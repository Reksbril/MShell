#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>

#include "config.h"
#include "siparse.h"
#include "utils.h"
#include "builtins.h"

#define MAX_PIPELINE_LENGTH MAX_LINE_LENGTH
#define MAX_SAVED_BACKGROUND_CHILDREN 1000

typedef struct bg_info {
    pid_t pid;
    int status;
    int signo; //jeżeli signo == -1, to znaczy że proces nie został zabity przez sygnał
} bg_info;


char buf[MAX_LINE_LENGTH + 1];
const int bufSize = MAX_LINE_LENGTH + 1;
int leftInbuf = 0; //liczba mówiąca, ile znaków pozostało nam do przetworzenia od ostatniego czytania
char *firstToCheck = buf; //wskaźnik do pierwszego elementu bufora, który nie został jeszcze przetworzony

sigset_t set; //zbiór sygnałów, które będziemy blokować
sigset_t empty_set; //pusty zbiór sygnałów

volatile int fg_count = 0; //zmienna pamiętająca liczbę działających procesów nie będących w tle
int pipeline_fg_count = 0; //zmienna pamiętająca, ile było procesów w danym pipeline
pid_t fg_tab[MAX_PIPELINE_LENGTH]; //tablica przechowująca działające procesy (nie będące w tle)
bg_info bg_finished[MAX_SAVED_BACKGROUND_CHILDREN]; //tablica przechowująca pid-y zakończonych procesów z tła
int bg_finished_count = 0; //licznik zakończonych procesów w tle
int prompt;
volatile char sig_flag = 0; //flaga oznaczająca, że otrzymaliśmy sygnał SIGINT podczas czytania
char *newLine;

void getArgs(char**, char*[], command*);
void printError(const char* filename, const char* errMessage);
void printSyntaxError();
void print_bg_info(int); //wypisuje informacje z tablicy bg_finished_count na pozycji podanej jako argument
void clear_zombie(); //funkcja sprawdza, czy są jakieś martwe procesy i się ich pozbywa
void kill_foreground(); //funkcja, która niszczy wszystkie procesy w foregroundzie

void handler(int);

void setSigAction(struct sigaction*, int);
void print_finished_bg();
int read_lines();
void move_buf();
int read_until_newline();
void open_redirs(command*); //otwiera pliki, do których przekierowujemy wejście/wyjście




int
main(int argc, char *argv[]) {
    struct sigaction sa1, sa2;


    //ustawianie zachowania w przypadku sygnałów sigint i sigchld
    setSigAction(&sa1, SIGINT);
    setSigAction(&sa2, SIGCHLD);


    //ustawiamy zbiór blokowanych sygnałów
    if(sigemptyset(&empty_set) ||
        sigemptyset(&set) ||
        sigaddset(&set, SIGCHLD)) {
        char* errmessage = strerror(errno);
        write(2, errmessage, strlen(errmessage));
        write(2, "\n", 1);
        exit(1);
    }


    pipelineseq *ln;
    command *com;

    struct stat st;

    fstat(0, &st);

    prompt = S_ISCHR(st.st_mode);


    char flag = 1;
    char eof = 0; //flaga mówiąca, czy dotarliśmy do końca pliku
    char background; //flaga mówiąca, czy komendy z danej linii będą uruchamiane w tle (czy jest & na końcu)


    while (1) {
        sigprocmask(SIG_SETMASK, &set, NULL); //blokujemy sygnał SIGCHLD

        if(prompt) {
            //wypisujemy informację o zakończonych procesach
            print_finished_bg();
        }
        else
            bg_finished_count = 0;
        int readRet = 0;
        if(!eof) {
            readRet = read_lines();
            firstToCheck = buf;
            flag = 1;
        }


        if(readRet < 0)
            exit(readRet);

        if (readRet == 0) {
            if(prompt || leftInbuf == 0)
                exit(readRet);
            else
                eof = 1;
        }


        while (1) { //dopóki nie doczytamy do końca bufora, przetwarzamy po kolei wszystkie linie
            clear_zombie();
            newLine = strchr(firstToCheck, '\n');


            if (newLine != NULL) {
                *newLine = '\0';
                ln = parseline(firstToCheck);
                firstToCheck = newLine + 1;
                leftInbuf = 0;
                flag = 1;
            } else {
                //Jeżeli nie znajdziemy znaku nowej lini, to:
                //1.Jeżeli jeszcze nie przesuwaliśmy polecenia na początek, to to robimy i ustawiamy flag = 0
                //2.W przeciwnym przypadku sprawdzamy, czy dotarliśmy do końca pliku. Jeżeli nie, to kasujemy resztę polecenia
                // (do rozpoczęcia nowej linii) i kontynuujemy pracę
                if(flag && strlen(firstToCheck) <= MAX_LINE_LENGTH) {
                    move_buf();
                    if(!eof)
                        leftInbuf = strlen(buf);
                    firstToCheck = buf;
                    flag = 0;
                    break;
                }
                else {
                    flag = 1;
                    newLine = strchr(firstToCheck, '\n');
                    if(newLine == NULL) {
                        if(eof) {
                            ln = parseline(firstToCheck);
                        }
                        else {
                            printSyntaxError();
                            readRet = read_until_newline();
                            leftInbuf = strlen(buf);
                            break;
                        }
                    }
                    else {
                        *newLine = '\0';
                        ln = parseline(firstToCheck);
                        leftInbuf = 0;
                    }
                }
            }

            if (ln == NULL) //przypadek, kiedy parsowanie się nie powiodło
                continue;


            pipelineseq* start = ln;
            do { //przeglądamy wszystkie pipeline
                commandseq *start_com = ln->pipeline->commands,
                            *current_com = start_com;
                background = (ln->pipeline->flags == INBACKGROUND);
                int old_fildes_in;
                int new_fildes[2];
                old_fildes_in = 0;
                int flag_last = 0;


                pipeline_fg_count = 0;
                do { //przeglądamy komenty w pipeline
                    //sprawdzanie błędów i pobieranie nazwy procesu i argumentów
                    com = current_com->com;
                    if(com == NULL && current_com != current_com->next) {
                        printSyntaxError();
                        break;
                    }
                    current_com = current_com->next;
                    if(current_com == start_com)
                        flag_last = 1;
                    if (com == NULL)
                        break;
                    char *pName;
                    char *argv[MAX_LINE_LENGTH];
                    getArgs(&pName, argv, com);

                    //sprawdzanie builtins
                    int ii = 0;
                    while (builtins_table[ii].name != NULL && strcmp(builtins_table[ii].name, pName))
                        ii++;
                    if (builtins_table[ii].name != NULL) {
                        builtins_table[ii].fun(argv);
                        continue;
                    }


                    if(flag_last)
                        new_fildes[1] = 1;
                    else {
                        if (pipe(new_fildes) == -1) {
                            write(2, "Pipe error!", 11);
                            continue;
                        }
                    }

                    int id = fork();

                    if (id != 0) {
                        if(old_fildes_in != 0)
                            close(old_fildes_in);
                        old_fildes_in = new_fildes[0];
                        if(new_fildes[1] != 1)
                            close(new_fildes[1]);
                        if(!background) {
                            fg_tab[fg_count++] = id; //jeżeli proces nie ma działać w tle, to dodajemy jego id to tablicy
                            pipeline_fg_count++;
                        }
                    } else {
                        if(background) {
                            setsid();
                            signal(SIGINT, SIG_DFL);
                        }

                        if(old_fildes_in != 0) {
                            close(0);
                            dup(old_fildes_in);
                            close(old_fildes_in);
                        }

                        if(new_fildes[1] != 1) {
                            close(1);
                            dup(new_fildes[1]);
                            close(new_fildes[1]);
                            close(new_fildes[0]);
                        }

                        open_redirs(com);
                        execvp(pName, argv);

                        //ERROR
                        char *errMessage = NULL;
                        if (errno == EACCES)
                            errMessage = "permission denied\n";
                        if (errno == ENOENT)
                            errMessage = "no such file or directory\n";
                        if (errMessage == NULL) //jeżeli nie wystąpił żaden z powyższych błędów
                            errMessage = "exec error\n";

                        printError(pName, errMessage);
                        exit(EXEC_FAILURE);
                    }
                } while(start_com != current_com);
                ln = ln->next;

                //printf("%d\n", fg_count);
                while(fg_count > 0)
                    sigsuspend(&empty_set);

            } while(start != ln);
        }
    }
}


void getArgs(char** n, char* a[], command* c) {
    argseq* firstArg = c->args;
    argseq* next = firstArg->next;
    *n = firstArg->arg;
    a[0] = firstArg->arg;
    int i = 1;
    while(firstArg != next) {
        a[i++] = next->arg;
        next = next->next;
    }
    a[i] = NULL;
}

void printError(const char* filename, const char* errMessage) {
    write(2, filename, strlen(filename));
    write(2, ": ", 2);
    write(2, errMessage, strlen(errMessage));
}

void printSyntaxError() {
    write(2, SYNTAX_ERROR_STR, strlen(SYNTAX_ERROR_STR));
    write(2, "\n", 1);
}


char wasInBackground(pid_t pid) { //funkcja sprawdzająca, czy dany proces był uruchomiony w te
    for(int i = 0; i < pipeline_fg_count; i++) {
        if(pid == fg_tab[i])
            return 0;
    }
    return 1;
}

void clear_zombie() {
    int status;
    pid_t pid;
    int sig_num;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        sig_num = -1;
        if(wasInBackground(pid)) {
            if(prompt) {
                if (WIFSIGNALED(status)) { //sprawdzamy, czy proces został zakończony prawidłowo
                    sig_num = WTERMSIG(status); //pobieramy numer sygnału, który zakończył nasz proces
                }
                //jako że chcemy wypisywać informacje o pewnej skończonej liczbie zakończonych procesów, to
                //bierzemy licznik modulo ograniczenie
                int bg_count = (bg_finished_count++) % MAX_SAVED_BACKGROUND_CHILDREN;
                bg_finished[bg_count].pid = pid;
                bg_finished[bg_count].signo = sig_num;
                bg_finished[bg_count].status = status;
            }
        }
        else
            fg_count--;
    }
}

void handler(int sig) {
    sig_flag = 1;
    clear_zombie();
}


void print_bg_info(int i) {
    char message[100];
    char termination_info[50];
    if(bg_finished[i].signo == -1)
        sprintf(termination_info, "(exited with status %d)", bg_finished[i].status);
    else
        sprintf(termination_info, "(killed by signal %d)", bg_finished[i].signo);
    int len = sprintf(message, "Background process %d terminated. %s\n", bg_finished[i].pid, termination_info);
    write(2, message, len);
}

void setSigAction(struct sigaction *sa, int signal) {
    sa->sa_handler = handler;
    if(sigemptyset(&sa->sa_mask) ||
       sigaddset(&sa->sa_mask, SIGCHLD) ||
       sigaddset(&sa->sa_mask, SIGINT)) {
        char* errmessage = strerror(errno);
        write(2, errmessage, strlen(errmessage));
        write(2, "\n", 1);
        exit(1);
    }

    //przechwytywanie sygnałów
    if (sigaction(signal, sa, NULL) == -1 ) {
        char* errmessage = strerror(errno);
        write(2, errmessage, strlen(errmessage));
        write(2, "\n", 1);
        exit(1);
    }
}

void print_finished_bg() {
    if(bg_finished_count > 0) {
        if(bg_finished_count > 1000)
            bg_finished_count = 1000;
        for(int i = 0; i < bg_finished_count; i++)
            print_bg_info(i);
        bg_finished_count = 0;
    }
    write(1, PROMPT_STR, sizeof(PROMPT_STR));
}

int read_lines() {
    int read_result;

    if(leftInbuf >= MAX_LINE_LENGTH) {
        leftInbuf = 0;
    }
    //printf("read1");
    sig_flag = 0;
    sigprocmask(SIG_SETMASK, &empty_set, NULL); //odblokowujemy sigchld

    read_result = read(0, buf + leftInbuf, bufSize - leftInbuf);
    while(sig_flag) {
        sig_flag = 0;
        write(1, "\n", 1);
        write(1, PROMPT_STR, sizeof(PROMPT_STR));
        read_result = read(0, buf + leftInbuf, bufSize - leftInbuf);
    }

    sigprocmask(SIG_SETMASK, &set, NULL);
    buf[read_result + leftInbuf] = '\0';
    return read_result;
}


void move_buf() {
    char tmp[MAX_LINE_LENGTH + 1];
    char *err1 = strcpy(tmp, firstToCheck);
    char *err2 = strcpy(buf, tmp);
    if (err1 == NULL || err2 == NULL) {
        write(1, "BŁĄD PRZY KOPIOWANIU STRINGA", 28);
        exit(1);
    }
}

int read_until_newline() {
    int read_result;

    while (newLine == NULL) {
        read_result = read(0, buf, bufSize);
        if (read_result < 0) {
            exit(read_result);
        }
        if (read_result == 0) { //przypadek, kiedy dotarliśmy do końca pliku
            exit(0);
        }
        newLine = strchr(buf, '\n');
    }
    firstToCheck = newLine + 1;
    buf[read_result] = '\0';

    move_buf();

    return read_result;
}

void open_redirs(command *com) {
    redirseq *first_red = com->redirs;
    redirseq *red = first_red;
    if (red != NULL) {
        do {
            if (IS_RIN(red->r->flags)) {
                close(0);
                int err = open(red->r->filename, O_RDONLY);
                if (err == -1) {
                    char *message;
                    write(2, red->r->filename, strlen(red->r->filename));
                    write(2, ": no such file or directory\n", 28);
                    exit(EXEC_FAILURE);
                }
            } else {
                mode_t mode;
                if (IS_ROUT(red->r->flags))
                    mode = O_WRONLY | O_CREAT | O_TRUNC;
                if (IS_RAPPEND(red->r->flags))
                    mode = O_WRONLY | O_CREAT | O_APPEND;
                close(1);
                int err = open(red->r->filename, mode, S_IRWXU);
                if (err == -1) {
                    write(2, red->r->filename, strlen(red->r->filename));
                    write(2, ": permission denied\n", 20);
                    exit(EXEC_FAILURE);
                }
            }
            red = red->next;
        } while (red != first_red);
    }
}