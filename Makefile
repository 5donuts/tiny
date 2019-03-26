All: tiny

tiny: main.c lexer parser
	gcc lex.yy.c parser.tab.c main.c -o tiny -Wall

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d parser.y

clean:
	rm -f *.tab.* *.yy.c out.o

target: out.s
	as out.s -o out.o
	ld -s -o out out.o

noexecs:
	rm -f tiny out
