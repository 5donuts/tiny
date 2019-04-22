#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"

// local function prototypes
static bool is_leaf(ast_node *node);

ast_node *ast_root; // root of the AST

// NB: see https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/

ast_node *new_ast_node(int node_type, ast_node *left, ast_node *right) {
  ast_node *node = malloc(sizeof(ast_node));
  memset(node, 0, sizeof(ast_node));

  node->node_type = node_type;
  node->left = left;
  node->right = right;

  return node;
}

ast_node *new_ast_symbol_reference_node(symrec *symbol) {
  ast_symbol_reference_node *node = malloc(sizeof(ast_symbol_reference_node));
  memset(node, 0, sizeof(ast_symbol_reference_node));

  node->node_type = SYMBOL_REFERENCE_NODE;
  node->symbol = symbol;

  return (ast_node *) node;
}

ast_node *new_ast_assignment_node(symrec *symbol, ast_node *value) {
  ast_assignment_node *node = malloc(sizeof(ast_assignment_node));
  memset(node, 0, sizeof(ast_assignment_node));

  node->node_type = ASSIGNMENT_NODE;
  node->symbol = symbol;
  node->value = value;

  return (ast_node *) node;
}

ast_node *new_ast_number_node(long int value) {
  ast_number_node *node = malloc(sizeof(ast_number_node));
  memset(node, 0, sizeof(ast_number_node));

  node->node_type = NUMBER_NODE;
  node->value = value;

  return (ast_node *) node;
}

ast_node *new_ast_function_node(symrec *symbol, ast_node *arguments) {
  ast_function_node *node = malloc(sizeof(ast_function_node));
  memset(node, 0, sizeof(ast_function_node));

  node->node_type = FUNCTION_NODE;
  node->symbol = symbol;
  node->arguments = arguments;

  return (ast_node *) node;
}

ast_node *new_ast_function_def_node(symrec *symbol, ast_node *arguments,
                                    ast_node *body) {
  ast_function_def_node *node = malloc(sizeof(ast_function_def_node));
  memset(node, 0, sizeof(ast_function_def_node));

  node->node_type = FUNCTION_DEF_NODE;
  node->symbol = symbol;
  node->arguments = arguments;
  node->body = body;

  return (ast_node *) node;
}

ast_node *new_ast_while_node(ast_node *condition, ast_node *while_branch) {
  ast_while_node *node = malloc(sizeof(ast_while_node));
  memset(node, 0, sizeof(ast_while_node));

  node->node_type = WHILE_NODE;
  node->condition = condition;
  node->while_branch = while_branch;

  return (ast_node *) node;
}

// recursively deallocate memory used by the tree
void free_ast_tree(ast_node *tree) {
  if (!tree) return; // handle case of NULL pointer

  switch (tree->node_type) {
    // two sub-trees
    case WHILE_NODE:
    case ADD_NODE:
    case SUB_NODE:
    case MUL_NODE:
    case DIV_NODE:
    case MOD_NODE:
    case LIST_NODE:
      free_ast_tree(tree->right);
      // fall through to one-subtree cases

    // one sub-tree
    case UMINUS_NODE:
    case BNEG_NODE:
    // case RETURN_NODE:
      free_ast_tree(tree->left);
      // fall through to no-subtree cases

    // no sub-trees
    case SYMBOL_REFERENCE_NODE:
    case NUMBER_NODE:
      break;

    // special cases
    case ASSIGNMENT_NODE:
      {
        ast_assignment_node *node = (ast_assignment_node *) tree;
        free_ast_tree(node->value);
      }
      break;
    case FUNCTION_NODE:
      {
        ast_function_node *node = (ast_function_node *) tree;
        free_ast_tree(node->arguments);
      }
      break;
    case FUNCTION_DEF_NODE:
      {
        ast_function_def_node *node = (ast_function_def_node *) tree;
        free_ast_tree(node->arguments);
        free_ast_tree(node->body);
      }
      break;

    // bad node type
    default:
      fprintf(stderr, "Error freeing ast_node of type %c\n",
              tree->node_type);
      break;
  }

  free(tree);
}

// recursively perform a DFS traversal of the AST
// NB: this produces the intermediate representation of the program
void traverse_tree(ast_node *tree) {
  if (!tree) return; // handle NULL pointers

  // evaluate leaf nodes
  if (is_leaf(tree)) {
    if (tree->node_type == SYMBOL_REFERENCE_NODE) {
      // TODO resolve the symbol
    }
    else if (tree->node_type == NUMBER_NODE) {
      // TODO process the constant
    }
  }

  // process non-leaf nodes
  else {
    switch (tree->node_type) {
      case ASSIGNMENT_NODE:
        // TODO evaluate value & store it in symbol
        break;

      case FUNCTION_NODE:
        // TODO make a function call with appropriate args
        break;

      case FUNCTION_DEF_NODE:
        // TODO build a function and add it to the placeholder list
        break;

      case WHILE_NODE:
        // TODO build the loop
        break;

      // TODO evaluate unary operator nodes
      case UMINUS_NODE:
      case BNEG_NODE:
      case LNEG_NODE: break;

      // TODO evaluate binary operator nodes
      case ADD_NODE:
      case SUB_NODE:
      case MUL_NODE:
      case DIV_NODE:
      case MOD_NODE: break;
    }
  }
}

// determine if a node in the AST is a leaf node
static bool is_leaf(ast_node *node) {
  if (!node) return false; // handle NULL pointers

  switch (node->node_type) {
    // no child nodes (i.e., leaf)
    case SYMBOL_REFERENCE_NODE:
    case NUMBER_NODE:
      return true;

    // one child node
    case ASSIGNMENT_NODE:
    case UMINUS_NODE:
    case BNEG_NODE:
    case LNEG_NODE:
      // fall through to two-child node cases

    // two child nodes
    case FUNCTION_NODE:
    case FUNCTION_DEF_NODE:
    case WHILE_NODE:
    case LIST_NODE:
    case ADD_NODE:
    case SUB_NODE:
    case MUL_NODE:
    case DIV_NODE:
    case MOD_NODE:
      return false;

    default:
      fprintf(stderr, "Error processing node of invalid type: %c\n",
              node->node_type);
      return false;
  }
}
