All: tiny

tiny: main.c lexer parser
	gcc lex.yy.c parser.tab.c symtab.c codegen.c main.c -o tiny -Wall

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d parser.y

target: out.s
	as out.s -o out.o
	ld -s -o out out.o

clean:
	rm -f *.tab.* *.yy.c tiny out*
