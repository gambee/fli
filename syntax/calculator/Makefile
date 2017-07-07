default: parser clean

parser: lex.yy.c bisonFiles
	gcc -lfl lex.yy.c parser.tab.c -o $@

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
