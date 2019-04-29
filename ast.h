#pragma once

#include "symtab.h"
#include "registers.h"

// NB: see https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/

// node types
#define SYMBOL_REFERENCE_NODE 'S'
#define SYMBOL_DECLARATION_NODE 'Y'
#define ASSIGNMENT_NODE 'A'
#define NUMBER_NODE 'N'
#define FUNCTION_NODE 'F'
#define FUNCTION_DEF_NODE 'D'
#define LIST_NODE 'L'
// #define RETURN_NODE 'R' // TODO figure out how to do return (as a "syscall"?)
#define WHILE_NODE 'W'
#define ADD_NODE '+'
#define SUB_NODE '-'
#define MUL_NODE '*'
#define DIV_NODE '/'
#define MOD_NODE '%'
#define UMINUS_NODE '_' /* unary negation */
#define BNEG_NODE '~'   /* bitwise negation */
#define LNEG_NODE '!'   /* logical negation */

// node for binary/unary operators & expression lists
typedef struct ast_node {
  char node_type;
  reg *res; // stores result of node evaluation (where applicable)
  struct ast_node *left;
  struct ast_node *right;
} ast_node;

// node for assignment statements
typedef struct ast_assignment_node {
  char node_type;
  reg *res;
  symrec *symbol;
  ast_node *value;
} ast_assignment_node;

// node to represent literals
typedef struct ast_number_node {
  char node_type;
  reg *res;
  long int value;
} ast_number_node;

// node for symbol references
typedef struct ast_symbol_reference_node {
  char node_type;
  reg *res;
  symrec *symbol;
} ast_symbol_reference_node;

// node for symbol declarations
typedef struct ast_symbol_declaration_node {
  char node_type;
  symrec *symbol;
} ast_symbol_declaration_node;

// node to represent a function call
typedef struct ast_function_node {
  char node_type;
  reg *res;
  ast_node *arguments;
  symrec *symbol;
} ast_function_node;

// node to represent a function definition
typedef struct ast_function_def_node {
  char node_type;
  ast_node *arguments; // NB: for now, don't support functions with arguments
  ast_node *body;
  symrec *symbol;
} ast_function_def_node;

// node to represent a while-loop
typedef struct ast_while_node {
  char node_type;
  ast_node *condition;
  ast_node *while_branch;
} ast_while_node;

// function prototypes
ast_node *new_ast_node(int, ast_node *, ast_node *);
ast_node *new_ast_assignment_node(symrec *, ast_node *);
ast_node *new_ast_number_node(long int);
ast_node *new_ast_symbol_reference_node(symrec *);
ast_node *new_ast_symbol_declaration_node(symrec *);
ast_node *new_ast_function_node(symrec *, ast_node *);
ast_node *new_ast_function_def_node(symrec *, ast_node *, ast_node *);
ast_node *new_ast_while_node(ast_node *, ast_node *);
void free_ast_tree(ast_node *);
void traverse_tree(ast_node *);
