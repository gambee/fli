%{
#include <stdio.h>
%}
%%
[ \t\n]		;
"("		{ printf("Found Left Parenthesis\n"); }
")"		{ printf("Found Right Parenthesis\n"); }
"->"		{ printf("Found Connective: Conditional\n"); }
"<->"		{ printf("Found Connective: Biconditional\n"); }
"^"		{ printf("Found Connective: Conjunction\n"); }
"v"		{ printf("Found Connective: Disjunction\n"); }
"~"		{ printf("Found Negation\n"); }
[TF]		{ printf("Found Logical Value: %s\n", yytext); }
%%
int main(int argc, char** argv) {
	yylex();
}
