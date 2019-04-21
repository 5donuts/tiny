SOURCES = lex.yy.c parser.tab.c symtab.c ast.c main.c

All: tiny

debug: main.c lexer parser
	gcc $(SOURCES) -g -o tiny -Wall

tiny: main.c lexer parser
	gcc $(SOURCES) -o tiny -Wall

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d -v parser.y

target: out.s
	as out.s -o out.o
	ld -s -o out out.o

clean:
	rm -f *.tab.* *.yy.c tiny out* parser.output
