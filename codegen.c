#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "codegen.h"

extern FILE *out; // the output file (see main.c)
// TODO write to intermediate file first?
// yeah, write to an intermediate file for pass 1
// then the output file for pass 2

// used to keep track of what registers are free
#define NUM_REGS 4
static char reg_names[NUM_REGS];
static bool reg_values[NUM_REGS];

void setup_for_codegen() {
  // make boilerplate assembly to start
  fprintf(out, ".text\n");
  fprintf(out, "\t.global _start\n\n");
  fprintf(out, "_start:\n");

  // init reg_names & reg_values
  reg_names = { "%%eax", "%%ebx", "%%ecx", "%%edx" };
  for (int i = 0; i < NUM_REGS; ++i)
    reg_values[i] = NULL;
}

// generate assembly code for system calls
void make_syscall(syscall *call) {
  // TODO save register values somewhere?
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

void make_unop(unop op, symrec *symbol) {
  switch(op) {
    case MINUS:
      // arithmetic negation (unary minus)
    case COMPL:
    case NOT:
    default:
      yyerror("Invalid unary operator");
      break;
  }
}
