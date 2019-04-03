#include "tiny.h"

extern FILE *yyin;

// initalize the symbol table
symrec *symtab = NULL;

// output file
FILE *out;

int main(int argc, char **argv) {
  ++argv, --argc; // skip over program name
  // either open file specified by command-line argument
  // or read from standard input
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;

  // open file for writing output
  out = fopen("out.s", "wb");

  // write boilerplate assembly to start
  fprintf(out, ".text\n");
  fprintf(out, "\t.global _start\n\n");
  fprintf(out, "_start:\n");

  // fprintf(out, "\tmovl\t$0, %%ebx\n"); // argument to system call
  yyparse(); // should emit the assembly for the return statement (prev. line)

  // write more boilerplate assembly to finish
  fprintf(out, "\tmovl\t$1, %%eax\n"); // system call number of sys_exit is 1
  fprintf(out, "\tint\t$0x80\n"); // send an interrupt

  // cleanup & exit
  fclose(out);
  return 0;
}

// add a symbol to the symbol table
// NB: the symbol table is LIFO
symrec *put_symbol(char *name) {
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
symrec *get_symbol(char *name) {
  symrec *sym;
  for (sym = symtab; sym != NULL; sym = (symrec *) sym->next) {
    if (strcmp(sym->name, name) == 0)
      return sym;
  }
  return NULL;
}
