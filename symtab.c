#include <stdlib.h>
#include <string.h>

#include "symtab.h"

// the symbol table
symrec *symtab = NULL;

// prototypes for local functions
static void put(symrec *); // add a symbol to the table
static void del(symrec *); // delete a symbol from the table
static void free_rec(symrec *); // completely free a record in the symbol table

/*
 * Perform a lookup in the symbol table for a symbol with "name"
 * If the node exists, return it. Otherwise, create a new node
 * in the symbol table for the specified name and return it
 */
symrec *lookup(char *name) {
  symrec *sym;

  // get the symbol if it already exists
  for (sym = symtab; sym != NULL; sym = sym->next) {
    if (strcmp(sym->name, name) == 0)
      return sym;
  }

  // make the symbol if it doesn't exist
  sym = malloc(sizeof(symrec));
  memset(sym, 0, sizeof(symrec));

  sym->name = (char *) malloc(strlen(name) + 1);
  strcpy(sym->name, name);
  put(sym);

  return sym;
}

// build an empty argument list
func_arglist *make_empty_arglist() {
  func_arglist *list = malloc(sizeof(func_arglist));
  memset(list, 0, sizeof(func_arglist));

  list->name = NULL;
  list->arg = VOID;
  list->next = NULL;

  return list;
}

// add a node to the symbol table in O(1)
static void put(symrec *sym) {
  sym->next = symtab;
  symtab = sym;
}

// remove a node from the symbol table in O(1)
static void del(symrec *sym) {
  symrec *next = sym->next;

  // handle case of NULL pointer
  if (!next) {
    free_rec(sym);
    sym = NULL;
  }

  // handle case of non-NULL pointer
  sym->name = next->name;
  sym->type = next->type;
  sym->ret_type = next->ret_type;
  sym->dat_type = next->dat_type;
  sym->arglist = next->arglist;
  sym->next = next->next;

  free_rec(next);
}

// free a record in the symbol table, as well as all of its elements
static void free_rec(symrec *sym) {
  free(sym->name); // free symbol name

  // free symbol arglist (if it exists)
  func_arglist *tmp;
  for(func_arglist *al = sym->arglist; al != NULL;) {
    tmp = al;
    al = al->next;
    free(tmp);
  }

  // don't free the pointer to the next struct, that's the responsibility of
  // the caller to handle

  free(sym);
}

// free the entire symbol table
void free_table() {
  symrec *tmp;
  for (symrec *sym = symtab; sym != NULL;) {
    tmp = sym;
    sym = sym->next;
    free_rec(tmp);
  }
}
