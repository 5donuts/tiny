// header guard
#ifndef TINY_H
#define TINY_H

// imports
#include <stdio.h> // for I/O
#include <stdlib.h> // malloc/free
#include <string.h> // memcpy/etc.

#include "parser.tab.h" // parser definitions

// new types/structures
typedef struct symbol { // defines a symbol in the symbol table (linked list)
  char *name; // name of the symbol
  struct symbol *next; // next item in linked list
} symbol;

// common function declarations
int yylex();
void yyerror(char *);
symbol *put_symbol(char *); // add a symbol to the symbol table
symbol *get_symbol(char *); // get a symbol from the symbol table

#endif // TINY_H
