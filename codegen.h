#pragma once

// syscall codes
#define SYS_EXIT 0x01

// line & sec data structures used to build assembly before writing to a file
// this approach allows things to be inserted, rearranged, etc. more easily
typedef struct line {
  char *text; // the text of this line of assembly
  struct line *next; // the next line in this section of assembly
} asm_line;

typedef struct sec {
  char *name; // name of the section
  asm_line *first, *last; // first and last lines in the section
  struct sec *next; // the next struct in the list
} asm_sec;

// function prototypes
void make_function(ast_function_def_node *);
void make_function_call(ast_function_node *);
void make_unary_op(ast_node *);
void make_binary_op(ast_node *);
void make_assignment(ast_assignment_node *);
void init_asm();
void write_asm();
void free_asm();
