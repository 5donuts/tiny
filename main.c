#include "tiny.h"

extern FILE *yyin;

int main(int argc, char **argv) {
  ++argv, --argc; // skip over program name
  // either open file specified by command-line argument
  // or read from standard input
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;

  yyparse(); // TODO change this too

  // hardcoded assembly
  // TODO change this
  FILE *out = fopen("out.s", "wb");
  fprintf(out, ".text\n");
  fprintf(out, "\t.global _start\n\n");
  fprintf(out, "_start:\n");
  fprintf(out, "\tmovl\t$0, %%ebx\n"); // argument to system call
  fprintf(out, "\tmovl\t$1, %%eax\n"); // system call number of sys_exit is 1
  fprintf(out, "\tint\t$0x80\n"); // send an interrupt

  // cleanup & exit
  fclose(out);
  return 0;
}
