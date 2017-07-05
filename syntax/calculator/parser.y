%{
#include <stdio.h>
int yylex(void);

void yyerror(char const *s)
{
	fprintf(stderr, "%s\n", s);
}
/* Tokens */
%}


%token CONDT BICND CJNCT DJNCT NEGTN
%token VALUE

%%

expr: 	expr conn expr
	| "(" expr ")"
	| "(" NEGTN VALUE ")"
	| VALUE
;

conn:	CONDT
	| BICND
	| CJNCT
	| DJNCT
;

%%

int main(int argc, char **argv)
{
	yyparse();
	return 0;
}
