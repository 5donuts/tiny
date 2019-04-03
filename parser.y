%{
  #include "tiny.h"
  extern FILE *out;
%}

/*
 * set up types for YYSTYPE.
 * see: https://stackoverflow.com/a/4288230/3646065
 * and: https://stackoverflow.com/a/12549501/3646065
 */
%union {
  long num;          /* constant integer value */
  /* symrec *ptr;       /* for returning symbol-table pointers */
}

%token TYPE IDENTIFIER RETURN
%token <num> NUMBER

%type <num> expression statement

%%

program: function
  ;

function: TYPE IDENTIFIER '(' ')' '{' statement '}'
  ;

statement: RETURN expression ';'  {
                                    fprintf(out, "\tmovl\t$%ld, %%ebx\n", $2);
                                  }
  ;

expression: NUMBER                { $$ = $1; }
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "error: %s\n", str);
}
