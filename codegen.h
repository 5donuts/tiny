#ifndef CODEGEN_H
#define CODEGEN_H

#include "symtab.h"

// definitions for supported linux syscalls
#define SYS_EXIT 0x01

// struct to hold a syscall code & its arguments
// TODO rewrite to not have hardcoded values in the assembly
typedef struct {
  int code; // in %eax
  void *arg1; // in %ebx
  void *arg2; // in %ecx
  void *arg3; // in %edx
  void *arg4; // in %esi // TODO remove these?
  void *arg5; // in %edi
} syscall;

// represents valid unary operators
typedef enum {
  MINUS, // unary negation
  COMPL, // one's complement
  NOT // logical NOT
} unop;

// function prototypes
void make_syscall(syscall *); // make a syscall with some arguments
void make_unop(unop, symrec *); // generate assembly to apply a unary operator

#endif // CODEGEN_H
