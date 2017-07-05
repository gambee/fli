%{
#include "parser.tab.h"
%}
%%
[ \t\n]		;
"(" | 
")" 		{ return yytext[0]; }
"->"		{ return CONDT; }
"<->"		{ return BICND; }
"^"		{ return CJNCT; }
"v"		{ return DJNCT; }
"~"		{ return NEGTN; }
[TF]		{ yylval = yytext[0] == 'T' ? 1 : 0; return VALUE; }
%%

