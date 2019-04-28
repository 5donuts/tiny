#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "ast.h"
#include "codegen.h"
#include "registers.h"

// NB: this includes the "0x" prefix; subtract 2 if you don't want that
#define NUM_HEX_DIGITS(n) ((int) (floor((log10(n) / log10(16)) + 3)))

extern FILE *out; // defined in main.c

// pointers for asm linked list
// NB: the list is FIFO
static asm_sec *head, *tail, *text_sec;
static int num_secs = 0;

// TODO always use tail as current section?
#define CUR_SEC tail

// local function prototypes
static asm_sec *get_sec(char *);
static asm_sec *make_sec(char *);
static void make_line(char *, asm_sec *);
static bool check_syscall(ast_function_node *);

// evaluate a function definition node
void make_function(ast_function_def_node *node) {
  // make a section for the function
  char *str;
  if (strcmp(node->symbol->name, "main") == 0) {
    str = (char *) malloc(6);
    memset(str, '\0', 6);
    sprintf(str, "%s", "_start"); // specify the program entry point
  }
  else {
    str = (char *) malloc(strlen(node->symbol->name) + 2);
    memset(str, '\0', strlen(node->symbol->name) + 2);
    sprintf(str, "%s:", node->symbol->name);
  }
  make_sec(str);
  free(str);

  // TODO evaluate argument nodes? Not sure how I want to implement these yet

  // evaluate child nodes to produce function body
  traverse_tree(node->body);
}

// evaluate a function call node
void make_function_call(ast_function_node *node) {
  if (check_syscall(node)) return; // process system calls

  // TODO be able to call other functions
}

// evaluate sub-expression and apply the unary operator to it
void make_unary_op(ast_node *node) {
  // evaluate sub-expression
}

void make_binary_op(ast_node *node) {
  // TODO implement this
}

void make_assignment(ast_assignment_node *node) {
  // TODO implement this
}

// set up for arranging strings of assembly code in memory
void init_asm() {
  // create the .text section
  asm_sec *sec = (asm_sec *) malloc(sizeof(asm_sec));
  memset(sec, 0, sizeof(asm_sec));
  sec->name = (char *) malloc(6);
  strcpy(sec->name, ".text");

  // set up pointers
  text_sec = head = tail = sec;
  num_secs++;
}

// write assembly to the output file
void write_asm() {
  for (asm_sec *s = head; s != NULL; s = s->next) {
    // write label for the section (.text section doesn't need ':' after label)
    fprintf(out, s == text_sec ? "%s\n" : "%s:\n", s->name);

    // write each line in the section
    for (asm_line *l = s->first; l != NULL; l = l->next)
      fprintf(out, "\t%s\n", l->text);
  }
}

// free memory resources
void free_asm() {
  for (asm_sec *s = head; s != NULL;) {
    // free each line in the section
    for (asm_line *l = s->first; l != NULL;) {
      asm_line *tmp = l;
      l = l->next;
      free(tmp);
    }

    // free the section
    asm_sec *tmp = s;
    s = s->next;
    free(tmp);
    num_secs--;
  }
}

// get the section with a matching name or NULL
static asm_sec *get_sec(char *name) {
  for (asm_sec *s = head; s != NULL; s = s->next) {
    if (strcmp(s->name, name) == 0)
      return s;
  }
  return NULL;
}

// add a section to the end of the list
static asm_sec *make_sec(char *name) {
  // make the sec
  asm_sec *sec = (asm_sec *) malloc(sizeof(asm_sec));
  memset(sec, 0, sizeof(asm_sec));
  sec->name = (char *) malloc(strlen(name) + 1);
  strcpy(sec->name, name);

  // add it to the list
  if (num_secs == 0)
    head = tail = sec;
  else {
    tail->next = sec;
    tail = sec;
  }
  num_secs++;

  // add a line for it in the .text section
  char str[strlen(name) + 8];
  sprintf(str, ".global\t%s", name);
  make_line(str, text_sec);

  return sec;
}

// "write" a line of assembly into a particular section
// NB: it's always added at the end of the section
static void make_line(char *text, asm_sec *sec) {
  // make the line
  asm_line *line = (asm_line *) malloc(sizeof(asm_line));
  memset(line, 0, sizeof(asm_line));
  line->text = (char *) malloc(strlen(text) + 1);
  strcpy(line->text, text);

  // add it to the section
  if (sec->first == NULL) {
    sec->first = sec->last = line;
  }
  else {
    sec->last->next = line;
    sec->last = line;
  }
}

// TODO finish this thing
// check if a function call is making a system call
// if it is, produce assembly for the syscall
// return true if it was a syscall, false otherwise
static bool check_syscall(ast_function_node *node) {
  bool is_syscall = false;
  // process sys_exit call
  if (strcmp(node->symbol->name, "exit") == 0) {
    // get argument to sys_exit
    ast_node *arg = node->arguments;
    switch(arg->node_type) {
      case SYMBOL_REFERENCE_NODE:
        {
          // get location for symbol
          symrec *sym = ((ast_symbol_reference_node *) arg)->symbol;
          reg *r = get_sym_reg(sym);
          if (r == get_reg(EBX))
            break; // the argument is already in the correct register

          // move argument to %ebx
          char str[15];
          sprintf(str, "movl\t%s,\t%s", r->name, EBX);
          make_line(str, CUR_SEC);
        }
        break;
      case NUMBER_NODE:
        {
          // move number into %ebx
          ast_number_node *num_node = (ast_number_node *) arg;
          char str[12 + NUM_HEX_DIGITS(num_node->value)];
          sprintf(str, "movl\t$%#lx,\t%s", num_node->value, EBX);
          make_line(str, CUR_SEC);
        }
        break;
      default:
        fprintf(stderr, "Error making sys_exit call with argument node of type"
                        "%c\n", arg->node_type);
        break;
    }
    // specify a call to sys_exit
    char str[12 + NUM_HEX_DIGITS(SYS_EXIT)];
    sprintf(str, "movl\t$%#x,\t%s", SYS_EXIT, EAX);
    make_line(str, CUR_SEC);
    is_syscall = true;
  }

  // make the interrupt
  if (is_syscall)
    make_line("int\t$0x80", CUR_SEC);

  return is_syscall;
}
