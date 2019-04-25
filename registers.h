#pragma once

#include <stdbool.h>

#include "symtab.h"

// representation of a CPU register
typedef struct reg {
  char *name; // name of the register (e.g., "%%eax")
  union {
    symrec *sym; // the symbol the register contains
    int lit; // the literal value the register contains
  } data;
  bool in_use; // true if the register contains something
  bool is_lit; // true if the register contains a literal
  struct reg *next; // next register in the linked list
} reg;

// function prototypes
reg *get_free_register();
void mark_free(reg *);
void init_registers();
void free_registers();
