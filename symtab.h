#ifndef SYMTAB_H
#define SYMTAB_H

// defines valid types for symbols in the symbol table
typedef enum { VAR, FUNC } symtype;

// defines a record in the symbol table
typedef struct symrec {
  char *name; // name of the symbol
  symtype type; // type of the symbol (VAR or FUNC)
  struct symrec *next; // next item in the linked list
} symrec;

// function prototypes
symrec *putsym(char *); // add a symbol to the symbol table
symrec *getsym(char *); // retrieve a symbol from the symbol table

#endif // SYMTAB_H
