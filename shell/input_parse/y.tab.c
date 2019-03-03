/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "siparse.y"
	#include <errno.h>
	#include <siparse.h>
	#include <stdio.h>

	#include "siparseutils.h"
    
	extern int yyleng;
	int parse_flags;

	int yylex(void);
	void yyerror(char *);
  
	void switchinputbuftostring(const char *);
	void freestringinputbuf(void);

	pipelineseq * parsed_line;
#line 21 "siparse.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
	int flags;
	char *name;
	argseq *args;
	redir *redir;
	redirseq *redirseq;
	command *comm;
	pipeline * pipeline;
	pipelineseq * pipelineseq;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 56 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define SSTRING 257
#define OAPPREDIR 258
#define COMMENT 259
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    3,    3,    4,    4,    2,    2,    1,    1,    5,
    5,    6,    6,    7,    8,    8,   10,   10,   11,    9,
    9,   12,   12,   13,   13,   14,   15,   15,   16,
};
static const YYINT yylen[] = {                            2,
    4,    1,    0,    1,    0,    1,    0,    3,    1,    1,
    1,    3,    1,    2,    1,    0,    2,    1,    1,    1,
    0,    2,    1,    1,    1,    2,    2,    2,    1,
};
static const YYINT yydefred[] = {                         0,
   19,    0,    0,    0,   13,    0,    0,   18,   10,   11,
    0,    0,    0,    0,    0,    0,   14,    0,   23,   24,
   25,   17,    2,    0,    0,   12,   29,   27,   26,   28,
   22,    4,    1,
};
static const YYINT yydgoto[] = {                          2,
    3,   11,   24,   33,   12,    4,    5,    6,   17,    7,
    8,   18,   19,   20,   21,   28,
};
static const YYINT yysindex[] = {                      -247,
    0,    0,  -38, -102,    0,  -56, -247,    0,    0,    0,
 -236, -247, -247, -247, -247, -247,    0,  -56,    0,    0,
    0,    0,    0,   22, -102,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yyrindex[] = {                         1,
    0,    0,    2,   14,    0,    3,    5,    0,    0,    0,
    8,    9,    1,    0,    0,    0,    0,    7,    0,    0,
    0,    0,    0,   25,   16,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,    0,    0,    0,   21,   23,    0,    0,    0,
   13,    0,   17,    0,    0,   15,
};
#define YYTABLESIZE 275
static const YYINT yytable[] = {                         10,
   16,    7,   21,   15,   15,   16,   20,    3,    6,    1,
   16,    7,   21,    9,   15,    8,   20,    3,    6,   22,
    9,   13,   23,    9,    5,    8,   27,   27,   27,   29,
   30,   32,   25,    0,   31,   26,    0,    0,   16,    0,
   21,    0,   15,    0,   20,    0,   16,    0,    0,    0,
    0,    9,    0,    8,    0,    0,    0,    0,    0,   16,
   16,   21,   16,   15,   15,   20,   15,   16,   16,    0,
   16,    0,    9,    0,    8,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   16,    0,   21,    0,   15,    0,
   20,    0,   16,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   14,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   16,   16,
    7,   21,   15,   15,    0,   20,   16,    6,    0,    0,
    0,    0,    9,    0,    8,
};
static const YYINT yycheck[] = {                         38,
    0,    0,    0,   60,    0,   62,    0,    0,    0,  257,
   10,   10,   10,    0,   10,    0,   10,   10,   10,    7,
   59,  124,  259,   10,    0,   10,   14,   15,   16,   15,
   16,   10,   12,   -1,   18,   13,   -1,   -1,   38,   -1,
   38,   -1,   38,   -1,   38,   -1,   38,   -1,   -1,   -1,
   -1,   38,   -1,   38,   -1,   -1,   -1,   -1,   -1,   59,
   60,   59,   62,   59,   60,   59,   62,   59,   60,   -1,
   62,   -1,   59,   -1,   59,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,  124,   -1,  124,   -1,
  124,   -1,  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  258,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  258,  259,
  259,  259,  258,  259,   -1,  259,  258,  259,   -1,   -1,
   -1,   -1,  259,   -1,  259,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 259
#define YYUNDFTOKEN 278
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"'&'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'","'<'",0,"'>'",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"SSTRING","OAPPREDIR","COMMENT",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : line",
"line : pipelineseq mpipelinesep mcomment mendl",
"mcomment : COMMENT",
"mcomment :",
"mendl : '\\n'",
"mendl :",
"mpipelinesep : pipelinesep",
"mpipelinesep :",
"pipelineseq : pipelineseq pipelinesep pipeline",
"pipelineseq : pipeline",
"pipelinesep : ';'",
"pipelinesep : '&'",
"pipeline : pipeline '|' single",
"pipeline : single",
"single : mnames mredirs",
"mnames : names",
"mnames :",
"names : names name",
"names : name",
"name : SSTRING",
"mredirs : redirs",
"mredirs :",
"redirs : redirs redir",
"redirs : redir",
"redir : redirIn",
"redir : redirOut",
"redirIn : '<' rname",
"redirOut : OAPPREDIR rname",
"redirOut : '>' rname",
"rname : name",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 175 "siparse.y"

void yyerror(char *s) {
	parse_flags|=YYERRORFLAG;
}


pipelineseq * parseline(char *str){
	int parseresult;

	parse_flags=0;
	resetutils();
	switchinputbuftostring(str);
	parseresult = yyparse();
	freestringinputbuf();

	if (parseresult){
		errno = parse_flags;
		return NULL;
	}
	return parsed_line;
}

#line 302 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 38 "siparse.y"
	{
			if (yystack.l_mark[-2].flags==INBACKGROUND){
				if  (push_last_to_bg(yystack.l_mark[-3].pipelineseq) != OK) {/* unexpected */ YYABORT;};
			}
			
			parsed_line = yystack.l_mark[-3].pipelineseq;
			yyval = yystack.l_mark[-3];
		}
break;
case 6:
#line 59 "siparse.y"
	{yyval.flags = yystack.l_mark[0].flags;}
break;
case 7:
#line 60 "siparse.y"
	{yyval.flags = 0;}
break;
case 8:
#line 65 "siparse.y"
	{
			if (yystack.l_mark[-1].flags==INBACKGROUND) push_last_to_bg(yystack.l_mark[-2].pipelineseq);
			yyval.pipelineseq = append_to_pipelineseq(yystack.l_mark[-2].pipelineseq, yystack.l_mark[0].pipeline);
			if (! yyval.pipelineseq) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 9:
#line 70 "siparse.y"
	{
			yyval.pipelineseq = start_pipelineseq(yystack.l_mark[0].pipeline);
			if (! yyval.pipelineseq) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 10:
#line 77 "siparse.y"
	{yyval.flags = 0;}
break;
case 11:
#line 78 "siparse.y"
	{yyval.flags = INBACKGROUND;}
break;
case 12:
#line 83 "siparse.y"
	{
			yyval.pipeline = append_to_pipeline(yystack.l_mark[-2].pipeline, yystack.l_mark[0].comm);
			if (! yyval.pipeline) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 13:
#line 87 "siparse.y"
	{
			yyval.pipeline = start_pipeline(yystack.l_mark[0].comm);
			if (! yyval.pipeline) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 14:
#line 94 "siparse.y"
	{
			if (yystack.l_mark[-1].args==NULL) {
				yyval.comm= NULL;	
			} else {
				command *com= new_command();
				if (!com) { parse_flags|=ALLOCFAILED; YYABORT;};
				com->args = yystack.l_mark[-1].args;
				com->redirs = yystack.l_mark[0].redirseq;
				yyval.comm = com;
			}
		}
break;
case 17:
#line 114 "siparse.y"
	{
			yyval.args = append_to_args(yystack.l_mark[-1].args, yystack.l_mark[0].name);
			if (! yyval.args) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 18:
#line 118 "siparse.y"
	{
			yyval.args= start_args(yystack.l_mark[0].name);
			if (! yyval.args) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 19:
#line 124 "siparse.y"
	{
			yyval.name= copytobuffer(yyval.name, yyleng+1);
			if (! yyval.name) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 22:
#line 136 "siparse.y"
	{
			yyval.redirseq = append_to_redirs(yystack.l_mark[-1].redirseq, yystack.l_mark[0].redir);
			if (! yyval.redirseq) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 23:
#line 140 "siparse.y"
	{
			yyval.redirseq = start_redirs(yystack.l_mark[0].redir); 
			if (! yyval.redirseq) { parse_flags|=ALLOCFAILED; YYABORT;};
		}
break;
case 26:
#line 152 "siparse.y"
	{ yystack.l_mark[0].redir->flags = RIN; yyval=yystack.l_mark[0]; }
break;
case 27:
#line 156 "siparse.y"
	{ yystack.l_mark[0].redir->flags = ROUT | RAPPEND ; yyval=yystack.l_mark[0]; }
break;
case 28:
#line 157 "siparse.y"
	{ yystack.l_mark[0].redir->flags = ROUT; yyval=yystack.l_mark[0]; }
break;
case 29:
#line 161 "siparse.y"
	{
			redir * red;

			red=new_redir();
			if (!red) { parse_flags|=ALLOCFAILED; YYABORT;};
			red->filename = yystack.l_mark[0].name;
			yyval.redir= red;
		}
break;
#line 632 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
