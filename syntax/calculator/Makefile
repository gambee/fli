all: lex.yy.c lexer.out

lex.yy.c: logic.l
	flex logic.l

lexer.out: lex.yy.c
	gcc -lfl lex.yy.c -o lexer.out
