#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registers.h"

#define NUM_REGS 8

// local function prototypes
static void put(reg *);
static reg *get(char *);

static reg *head; // beginning of the list

// names of registers that can be used by tiny
static const char reg_names[] = { "%%eax", "%%ebx", "%%ecx", "%%edx", "%%esp",
                                  "%%ebp", "%%esi", "%%edi" };

// get a free register or NULL
reg *get_free_register() {
  for (reg *r = head; r != NULL; r = r->next) {
    if (!r->in_use)
      return r;
  }
  return NULL;
}

// initialize the linked-list of registers
void init_registers() {
  // build each register & add it to the list
  for (int i = 0; i < NUM_REGS; ++i) {
    reg *r = malloc(sizeof(reg));
    r->name = reg_names[i];
    r->in_use = r->is_lit = false;
    put(r);
  }
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

// get a register from the list
static reg *get(char *name) {
  for (reg *r = head; r != NULL; r = r->next) {
    if (strcmp(r->name, name) == 0)
      return r;
  }
  return NULL;
}
