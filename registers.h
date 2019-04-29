#pragma once

#include <stdbool.h>

#include "symtab.h"

// register names
#define EAX "%eax"
#define EBX "%ebx"
#define ECX "%ecx"
#define EDX "%edx"
#define ESP "%esp"
#define EBP "%ebp"
#define ESI "%esi"
#define EDI "%edi"

// representation of a CPU register
typedef struct reg {
  char *name; // name of the register (e.g., "%%eax")
  // union {
  //   symrec *sym; // the symbol the register contains
  //   literal *lit; // the literal value the register contains
  // } data;
  symrec *sym; // the symbol in the register (unless it contains a literal)
  bool in_use; // true if the register contains something
  bool is_lit; // true if the register contains a literal
  struct reg *next; // next register in the linked list
} reg;

// function prototypes
reg *get_free_register();
reg *get_sym_reg(symrec *);
reg *get_reg(char *);
void put_val(long int);
void put_sym(symrec *, long int);
void free_reg(reg *, bool);
void init_registers();
void free_registers();
