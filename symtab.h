#pragma once

// defines valid types for symbols in the symbol table
typedef enum { VAR, FUNC } symtype;

// types allowed for variables & function return types
enum type { INT, VOID };
typedef struct func_arglist {
  char *name; // name of the symbol used for this arg
  enum type arg; // the type of this arg
  struct func_arglist *next; // next argument (or NULL)
} func_arglist;

// defines a record in the symbol table
typedef struct symrec {
  char *name; // name of the symbol
  symtype type; // type of the symbol
  // enum type ret_type; // for functions
  // enum type dat_type; // for variables
  func_arglist *arglist; // argument list for functions
  struct symrec *next; // next item in the linked list
} symrec;

// function prototypes
symrec *lookup(char *);
func_arglist *make_empty_arglist(); // TODO remove this
void free_table();
