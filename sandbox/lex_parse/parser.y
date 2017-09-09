%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "slee.h"

char result;
char *pfix, *ifix;
struct ast_node* ast_root;


int yylex(void);

void yyerror(char const *s)
{
	fprintf(stderr, "%s\n", s);
}
/* Tokens */
%}

%union{
	struct ast_node* node_ptr;
	int token_type;
}

%token <token_type> CONDT BICND CJNCT DJNCT
%type <node_ptr> formula expr
%type <token_type> value conn
%%

start:
	  formula
	  		{		pfix = NULL;
					ifix = NULL;
					ast_root = $1;
					write_postfix(ast_root, &pfix);
					write_infix(ast_root, &ifix);
					SLEE_eval(pfix, &result);
					printf("%s evaluates to %c\n", ifix, (result == '1' ? 'T' : result == '0' ? 'F' : result));
}
	| start formula
	  		{		pfix = NULL;
					ifix = NULL;
					ast_root = $2;
					write_postfix(ast_root, &pfix);
					write_infix(ast_root, &ifix);
					SLEE_eval(pfix, &result);
					printf("%s evaluates to %c\n", ifix, (result == '1' ? 'T' : result == '0' ? 'F' : result));
}
;
/*
formulas:
		formula
	|	formula formulas
	*/

formula:
		expr		{$$ = $1;}
/*	|	'~' expr 	{$$ = new_node('~', NULL, $2);} */
	|	expr conn expr	{$$ = new_node($2, $1, $3);}
;

expr:
		value		{$$ = new_node($1, NULL, NULL); }
	|	'~' expr	{$$ = new_node('~', NULL, $2); }
	|	'(' formula ')'	{$$ = $2;}
;

conn:
		CONDT		{$$ = CONDT;}
	|	BICND		{$$ = BICND;}
	|	CJNCT		{$$ = CJNCT;}
	|	DJNCT		{$$ = DJNCT;}
;

value: 'T'			{$$ = (int) 'T';}
     | 'F'			{$$ = (int) 'F';}
;

%%

int main(int argc, char **argv)
{
	SLEE_init();
	yyparse();
	return 0;
}
