%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
struct node* ast_root;


int yylex(void);

void yyerror(char const *s)
{
	fprintf(stderr, "%s\n", s);
}
/* Tokens */
%}

%union{
	struct node* node_ptr;
	int token_type;
}

%token <token_type> CONDT BICND CJNCT DJNCT
%type <node_ptr> formula expr
%type <token_type> value conn
%%

start: formula {ast_root = $1;}
;

formula:
		expr		{$$ = $1;}
	|	'~' expr 	{$$ = new_node('~', $2, NULL);}
	|	expr conn expr	{$$ = new_node($2, $1, $3);}
;

expr:
		value		{$$ = new_node($1, NULL, NULL); }
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
/*
	yyparse();
	if(argc == 2)
		save_as_dot(argv[1], ast_root);
	else
		print_as_dot(stdout, ast_root);
*/
	struct node tmp;
	printf("ret of set_token_value(&tmp, 5)\n", set_token_value(&tmp, 5));
	printf("value of tmp.token_value: %d\n", tmp.token_value);
	printf("ret of set_token_value(NULL, 12): %d\n", set_token_value(NULL, 12));
	return 0;
}
