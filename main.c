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
