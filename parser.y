%{
  #include <stdio.h>

  #include "symtab.h" // symbol table definitions & function declarations
  #include "codegen.h" // code generation definitions & function declarations

  void yyerror(char *);
  int yylex(void); // defined by lexer

  extern int yylineno; // defined by lexer
%}

/* TODO actually implement these
 * set up types for YYSTYPE.
 * see: https://stackoverflow.com/a/4288230/3646065
 * and: https://stackoverflow.com/a/12549501/3646065
 */
%union {
  long num;          /* constant integer value TODO add more */
}
%type <num> expression statement

%token TYPE IDENTIFIER RETURN
%token <num> NUMBER

%right '-' '~' '!'

%%

program:
  function
  ;

function:
  TYPE IDENTIFIER '(' ')' '{' statement_list '}'
  ;

statement_list:
  statement_list statement
  | statement
  | /* empty */
  ;

statement:
  RETURN expression ';'  { // TODO change this
                           int exit_code = $2;
                           syscall call;
                           call.code = SYS_EXIT;
                           call.arg1 = &exit_code;
                           make_syscall(&call);
                         }
  ;

expression:
  unary_op expression   { // TODO add expressions to AST & evaluate them??
                          // TODO figure this out
                        }
  | NUMBER              { $$ = $1; }
  ;

unary_op:
  '!'
  | '~'
  | '-'
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "Error | Line: %d\n\t%s\n", yylineno, str);
}
