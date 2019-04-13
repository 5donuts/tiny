#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"

extern FILE *out; // the output file (see main.c)

// generate assembly code for system calls
void make_syscall(syscall *call) {
  // put arguments in appropriate registers depending on the syscall
  switch (call->code) {
    case SYS_EXIT:
      fprintf(out, "\tmovl\t$%d, %%ebx\n", *((int *) call->arg1));
      break;
    default:
      fprintf(stderr, "Error, syscall code %x unrecognized\n", call->code);
      exit(1);
  }
  // make the syscall
  fprintf(out, "\tmovl\t$%x, %%eax\n\tint\t$0x80\n", call->code);
}
