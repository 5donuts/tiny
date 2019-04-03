# Tiny
A toy C compiler

# Building Tiny
Tiny can be compiled using `make` (assuming you have `flex` and `bison` installed), or manually as follows:

    bison -d parser.y
    flex lexer.l
    gcc lex.yy.c parser.tab.c main.c -o tiny

# Usage
C programs that Tiny is able compile can be produced using `make` as follows:

    ./tiny <program>
    make target
Note that if you use the `make` method, your executable will be called `out`.
Alternatively, you can manually produce programs using Tiny as follows:

    ./tiny <program>
    as out.s -o out.o
    ld -s -o <executable_name> out.o
# Supported C Features
Currently, Tiny supports the following operations:

* Unary negation (`-`)
* Logical negation (`!`)
* Bitwise complement (`~`)
