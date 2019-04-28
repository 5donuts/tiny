SOURCES = lex.yy.c parser.tab.c symtab.c ast.c registers.c codegen.c main.c
CFLAGS = -Wall -lm

All: tiny

tiny: main.c lexer parser
	gcc $(SOURCES) $(CFLAGS) -o tiny

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d -v parser.y

target: out.s
	as out.s -o out.o
	ld -s -o out out.o

clean:
	rm -f *.tab.* *.yy.c tiny out* parser.output
