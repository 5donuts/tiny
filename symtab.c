#include <stdlib.h>
#include <string.h>

#include "symtab.h"

// the symbol table
symrec *symtab = NULL;

// add a symbol to the symbol table
// NB: the symbol table is LIFO
symrec *putsym(char *name) {
  // build the new symbol struct
  symrec *sym = (symrec *) malloc(sizeof(symrec));
  sym->name = (char *) malloc(strlen(name) + 1);
  strcpy(sym->name, name);

  // add the new symbol at the beginning of the list
  sym->next = (struct symrec *) symtab;
  symtab = sym;

  // return a pointer to the symbol
  return sym;
}

// perform a linear search for a symbol with the given name
// NB: returns either the symbol or NULL
symrec *getsym(char *name) {
  symrec *sym;
  for (sym = symtab; sym != NULL; sym = (symrec *) sym->next) {
    if (strcmp(sym->name, name) == 0)
      return sym;
  }
  return NULL;
}
