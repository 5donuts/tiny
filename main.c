#include <stdio.h>
#include <stdlib.h> // malloc, free, etc.
#include <string.h> // memcpy, strcmp, etc.

#include "symtab.h" // symbol table definitions & function prototypes
#include "ast.h"  // AST definitions & function prototypes
#include "registers.h" // CPU register representation
#include "codegen.h" // code generation routines

extern FILE *yyin; // defined by lexer
extern ast_node *ast_root; // defined in ast.c
extern symrec *symtab; // defined in symtab.c

// external function prototypes
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

  // build the AST
  if (yyparse() != 0) {
    printf("\nEncountered an error while building AST\n");
    exit(1);
  }

  // either write to "out.s" or file specified by command-line argument
  if (argc > 1)
    out = fopen(argv[1], "wb");
  else
    out = fopen("out.s", "wb");

  // traverse the AST and produce assembly
  init_asm();
  traverse_tree(ast_root);
  write_asm();

  // cleanup & exit
  if (argc > 0)
    fclose(yyin);
  fclose(out);
  free_asm();
  free_registers();
  free_ast_tree(ast_root);
  free_table();

  return 0;
}
