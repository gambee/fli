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

formula:
		expression
	|	NEGTN expression
	|	expression connective expression
;

expression:
		VALUE
	|	"(" formula ")"
;

connective:
		CONDT
	|	BICND
	|	CJNCT
	|	DJNCT
;

%%

int main(int argc, char **argv)
{
	yyparse();
	return 0;
}
