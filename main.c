#include <stdio.h>
#include <stdlib.h> // malloc, free, etc.
#include <string.h> // memcpy, strcmp, etc.

#include "symtab.h" // symbol table definitions & function prototypes
#include "ast.h"  // AST definitions & function prototypes

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

  // TODO open file for writing output
  // out = fopen("out.s", "wb");

  // TODO traverse the AST to produce initial output w/placeholders
  // TODO substitute placeholders in the output file

  // cleanup & exit
  // TODO fclose(out);
  if (argc > 0)
    fclose(yyin);
  free_ast_tree(ast_root);
  free_table();
  return 0;
}
