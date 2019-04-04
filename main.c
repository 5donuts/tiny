#include <stdio.h>
#include <stdlib.h> // malloc, free, etc.
#include <string.h> // memcpy, strcmp, etc.

#include "symtab.h" // symbol table definitions & function declarations
#include "codegen.h" // code generation definitions & function declarations

extern FILE *yyin; // defined by lexer

int yylex(void); // defined by lexer
int yyparse(void); // defined by parser
void yyerror(char *); // defined in parser.y

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

  yyparse(); // TODO work on parsing & stuff

  // cleanup & exit
  fclose(out);
  return 0;
}

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

// generate assembly code for system calls
void make_syscall(syscall *call) {
  // perform per-call operations
  int *exit_code;
  switch (call->code) {
    case SYS_EXIT:
      exit_code = call->arg1;
      fprintf(out, "\tmovl\t$%d, %%ebx\n", *exit_code);
      break;
    default:
      fprintf(stderr, "Error, syscall code %x unrecognized\n", call->code);
      exit(1);
  }
  // make the syscall
  fprintf(out, "\tmovl\t$%x, %%eax\n\tint\t$0x80\n", call->code);
}
