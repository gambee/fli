%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);

void yyerror(char const *s)
{
	fprintf(stderr, "%s\n", s);
}
/* Tokens */
%}
%union {
	int i;
	struct node* root;

%token CONDT BICND CJNCT DJNCT
%token VALUE

%%

formula:
		expression
	|	'~' expression
	|	expression connective expression { $$ = new_node(
;

expression:
		VALUE
	|	'(' formula ')'
;

connective:
		CONDT
	|	BICND
	|	CJNCT
	|	DJNCT
;

%%

#include "ast.h"

int main(int argc, char **argv)
{
	yyparse();
	return 0;
}
