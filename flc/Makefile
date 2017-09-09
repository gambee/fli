default: linux 

dbg: lex.yy.c bisonFiles
	gcc -g -lfl lex.yy.c parser.tab.c -o flc_db

osx_dbg: lex.yy.c bisonFiles
	gcc -g -ll lex.yy.c parser.tab.c -o flc_db

linux: lex.yy.c bisonFiles
	gcc -lfl lex.yy.c parser.tab.c -o flc

osx: lex.yy.c bisonFiles
	gcc -ll lex.yy.c parser.tab.c -o flc

lex.yy.c: lexer.l
	flex $<

bisonFiles: parser.y
	bison -d $<

parser.output:
	bison -v parser.y

ast: ast.dot
	dot -Tsvg ast.dot > ast.svg

clean: 
	rm lex.yy.c parser.tab.h parser.tab.c
