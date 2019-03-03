#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

#include "builtins.h"


int ex(char*[]);
int echo(char*[]);
int undefined(char *[]);
int cd(char *[]);
int ls(char *[]);
int myKill(char *[]);

builtin_pair builtins_table[]={
	{"exit",	&ex},
	{"lecho",	&echo},
    //{"echo",    &echo},
	{"lcd",		&cd},
    {"cd",      &cd},
	{"lkill",	&myKill},
	{"lls",		&ls},
	{NULL,NULL}
};

int 
echo( char * argv[])
{
	int i =1;
	if (argv[i]) printf("%s", argv[i++]);
	while  (argv[i])
		printf(" %s", argv[i++]);

	printf("\n");
	fflush(stdout);
	return 0;
}

int 
undefined(char * argv[])
{
	fprintf(stderr, "Command %s undefined.\n", argv[0]);
	return BUILTIN_ERROR;
}

int
ex(char * argv[]) 
{
   exit(0);
}

int
cd(char * argv[]) 
{
    int err;
    if(argv[1] == NULL)
        err = chdir(getenv("HOME"));
    else {
    	if(argv[2] != NULL)
    		err = -1;
		else
			err = chdir(argv[1]);
	}
    if(err == -1)
    	fprintf(stderr, "Builtin lcd error.\n");
    return err;
}

int
ls(char* argv[]) {
	struct dirent **namelist;
	int i,n;


	n = scandir(".", &namelist, 0, 0);
	if (n < 0) {
		fprintf(stderr, "Builtin lls error.\n");
		return n;
	}
	else {
		for (i = 0; i < n; i++) {
			if(namelist[i]->d_name[0] == '.')
				continue;
			write(1, namelist[i]->d_name, strlen(namelist[i]->d_name));
			write(1, "\n", 1);
			free(namelist[i]);
		}
	}
	free(namelist);
	return(0);
}

int
myKill(char* argv[]) {
	int error = 0;
	int signal;
	pid_t pid;
	char *endptr;
	if(argv[1] == NULL) {
		fprintf(stderr, "Builtin lkill error.\n");
		return(1);
	}
	if(argv[1][0] == '-') {
		signal = strtol(argv[1] + 1, &endptr, 10);
		if(strlen(endptr) > 0)
		    error = 1;
		pid = strtol(argv[2], &endptr, 10);
		if(!signal || !pid || strlen(endptr) > 0)
			error = 1;
	}
	else {
		signal = SIGTERM;
		pid = strtol(argv[1], &endptr, 10);
		if(!pid || strlen(endptr) > 0)
			error = 1;
	}
	if(error) {
		fprintf(stderr, "Builtin lkill error.\n");
		return(1);
	}
	int k = kill(pid, signal);
	if(k == -1)
		fprintf(stderr, "Builtin lkill error.\n");
	return(k);
}
