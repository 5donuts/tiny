# Tiny
A toy C compiler

# Building Tiny
Build Tiny using `make`, or with the following commands:

    flex lexer.l
    bison -d parser.y
    gcc lex.yy.c parser.tab.c symtab.c ast.c main.c -o tiny -Wall

# Usage
You can use Tiny to produce executables using `make` as follows:

    ./tiny /path/to/prog.c
    make target

Note that if you use the `make` method, your executable will be called `out`.
Alternatively, you can manually produce programs using Tiny as follows:

    ./tiny /path/to/prog.c
    as out.s -o out.o
    ld -s -o <executable_name> out.o
