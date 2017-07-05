default: parser clean

keep: parser

lex.yy.c: lexer.l
	flex $<
logic.tab.h: parser.y
	bison -d $<

parser: lex.yy.c parser.tab.h
	gcc -lfl lex.yy.c parser.tab.c -o $@

clean: 
	rm lex.yy.c parser.tab.h parser.tab.c
