%{
#include "parser.tab.h"
%}
%%
[ \t\n]		;

"(" | 
")" 	{	/*DB fprintf(stderr, "\'%c\' ", *yytext); DB*/
		return *yytext;	
	}

"->"	{ 	/*DB fprintf(stderr,
				//DB_TKN "CONDT "
				//DB_TXT "\'->\' "
		); DB*/
		return CONDT;
	}

"<->"	{	/*DB fprintf(stderr,
			//DB_TKN "BICND "
			//DB_TXT "\'<->\' "
		); DB*/
		return BICND;
	}

"^"	{	/*DB fprintf(stderr,
			//DB_TKN "CJCNT "
			//DB_TXT "\'^\' "
		); DB*/
		return CJNCT;
	}

"v"	{	/*DB fprintf(stderr,
			//DB_TKN "DJCNT "
			//DB_TXT "\'v\' "
		); DB*/
		return DJNCT;
	}

"~"	{	/*DB fprintf(stderr, "\'~\' "); DB*/
		return *yytext;
	}

[TF]	{
		return *yytext;
	}

.	{
		fprintf(stderr, "ERROR: lexer.l: Unrecognized Token: %s\nParse Process Terminating...\n", yytext);
		return 0;
	}
%%

