#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registers.h"

#define NUM_REGS 8

// local function prototypes
static void put(reg *);

static reg *head; // beginning of the list

// names of registers that can be used by tiny
static const char reg_names[] = { EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI };

// get a free register or NULL
reg *get_free_register() {
  for (reg *r = head; r != NULL; r = r->next) {
    if (!r->in_use)
      return r;
  }
  return NULL;
}

// get the register containing sym or NULL
reg *get_sym_reg(symrec *sym) {
  for (reg *r = head; r != NULL; r = r->next) {
    if (r->in_use && !r->is_lit) {
      if (sym == r->data.sym)
        return r; // if the pointers are the same, it's the same symbol
    }
  }
  return NULL;
}

// get a specific register from the list or NULL
reg *get_reg(char *name) {
  for (reg *r = head; r != NULL; r = r->next) {
    if (strcmp(r->name, name) == 0)
      return r;
  }
  return NULL;
}

// free a register, and store it's value if specified
void free_reg(reg *r, bool store_val) {
  if (store_val) {
    // TODO store the value somewhere
  }

  // clear the register's contents & mark it free
  r->data.lit = 0;
  r->in_use = false;
  r->is_lit = false;
}

// initialize the linked-list of registers
void init_registers() {
  // build each register struct & add it to the list
  for (int i = 0; i < NUM_REGS; ++i) {
    reg *r = malloc(sizeof(reg));
    r->name = reg_names[i];
    r->in_use = r->is_lit = false;
    put(r);
  }

  // flag esp and ebp as in-use
  reg *r = get_reg(ESP);
  r->in_use = r->is_lit = true;
  r = get_reg(EBP);
  r->in_use = r->is_lit = true;
}

// free all registers in the linked list
void free_registers() {
  for (reg *r = head; r != NULL;) {
    reg *tmp = r;
    r = r->next;
    free(tmp);
  }
}

// add a register to the list
static void put(reg *reg) {
  reg->next = head;
  head = reg;
}
