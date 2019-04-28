%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "ast.h"  // AST definitions & function prototypes
  #include "symtab.h" // symbol table definitions & function prototypes

  void yyerror(char *);
  int yylex(void); // defined by lexer

  extern int yylineno; // defined by lexer
  extern ast_node *ast_root; // defined in ast.c

  // NB: see https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
%}

/*
 * Set up types for YYSTYPE.
 * see: https://stackoverflow.com/a/4288230/3646065
 * and: https://stackoverflow.com/a/12549501/3646065
 */
%union {
  long num;                 /* constant integer value */
  struct ast_node *ast;     /* a node in the AST for non-terminal symbols */
  struct symrec *symbol;    /* a record in the symbol table for an identifier */
  enum type val_type;       /* a function return type or variable type */
}

/* token declarations */
/* TODO figure out how to implement RETURN
   last attempt caused shift/reduce errors */
%token <num> NUMBER
%token <symbol> IDENTIFIER
%token <val_type> TYPE
%token RETURN WHILE END

/* precedence declarations, lower is higher */
%left ','
%right '='
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '~' '!'
%left '(' ')'

/* non-terminal symbol declarations */
%type <ast> expression exp_list
%type <ast> statement statement_list
%type <ast> function function_list

%%

program
  : function_list { ast_root = $1; }
  ;

function_list
  : function function_list  { $$ = new_ast_node(LIST_NODE, $1, $2); }
  | function END            { $$ = $1; YYACCEPT; /* stop parsing */ }
  ;

function
  : TYPE IDENTIFIER '(' ')' '{' statement_list '}'
    {
      /* $2->ret_type = $1; */
      $2->type = FUNC;
      $2->arglist = NULL; /* TODO find other calls to make_empty_arglist() & remove */
      ast_root = new_ast_function_def_node($2, NULL, $6);
    }
  ;

statement_list
  : statement statement_list  { $$ = new_ast_node(LIST_NODE, $1, $2); }
  | statement                 { $$ = $1; }
  ;

statement
  : expression ';'                     { $$ = $1; }
  | WHILE '(' expression ')' statement { $$ = new_ast_while_node($3, $5); }
  ;

exp_list
  : expression ',' exp_list  { $$ = new_ast_node(LIST_NODE, $1, $3); }
  | expression               { $$ = $1; }
  ;

expression
  : '(' expression ')'          { $$ = $2; }
  | '-' expression %prec UMINUS { $$ = new_ast_node(UMINUS_NODE, $2, NULL); }
  | '~' expression              { $$ = new_ast_node('~', $2, NULL); }
  | '!' expression              { $$ = new_ast_node('!', $2, NULL); }
  | expression '+' expression   { $$ = new_ast_node('+', $1, $3); }
  | expression '-' expression   { $$ = new_ast_node('-', $1, $3); }
  | expression '*' expression   { $$ = new_ast_node('*', $1, $3); }
  | expression '/' expression   { $$ = new_ast_node('/', $1, $3); }
  | expression '%' expression   { $$ = new_ast_node('%', $1, $3); }
  | NUMBER                      { $$ = new_ast_number_node($1); }
  | TYPE IDENTIFIER             { $2->dat_type = $1;
                                  $$ = new_ast_symbol_reference_node($2);
                                }
  | IDENTIFIER '=' expression   { $$ = new_ast_assignment_node($1, $3); }
  | IDENTIFIER '(' ')'          { $$ = new_ast_function_node($1, NULL); }
  | IDENTIFIER '(' exp_list ')' { $$ = new_ast_function_node($1, $3); }
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "Error on Line %d: %s: ", yylineno, str);
}
