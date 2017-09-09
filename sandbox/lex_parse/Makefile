default: parser clean

parser: lex.yy.c bisonFiles sleeFiles 
	gcc -lfl lex.yy.c parser.tab.c -o $@

sleeFiles: ../../slee/slee_alphabet.h ../../slee/slee.h ../../slee/fli_stack.h
	cp ../../slee/slee_alphabet.h ./
	cp ../../slee/slee.h ./
	cp ../../slee/fli_stack.h ./

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
