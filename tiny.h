// header guard
#ifndef TINY_H
#define TINY_H

// imports
// TODO only have imports that are actually necessary here
// don't need to bloat tiny.h with #include's
#include <stdio.h> // for I/O
#include <stdlib.h> // malloc/free
#include <string.h> // memcpy/etc.

#include "parser.tab.h" // parser definitions

// defines valid types for symbols in the symbol table
typedef enum { VAR, FUNC } symtype;

// defines a symbol in the symbol table
typedef struct symrec {
  char *name; // name of the symbol
  symtype type; // type of the symbol (VAR or FUNC)
  struct symrec *next; // next item in linked list
} symrec;

// common function declarations
int yylex();
void yyerror(char *);
symrec *put_symbol(char *); // add a symbol to the symbol table
symrec *get_symbol(char *); // get a symbol from the symbol table

#endif // TINY_H
