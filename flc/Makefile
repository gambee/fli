default: flc 

dbg: lex.yy.c bisonFiles
	gcc -g -lfl lex.yy.c parser.tab.c -o $@

flc: lex.yy.c bisonFiles
	gcc -lfl lex.yy.c parser.tab.c -o $@

flc_macOS: lex.yy.c bisonFiles
	gcc -ll lex.yy.c parser.tab.c -o $@

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
