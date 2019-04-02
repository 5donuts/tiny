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

%token INCLUDE HEADER_FILE
%token TYPE IDENTIFIER RETURN
%token <num> NUMBER

%%

program: header function
  | function
  ;

header: INCLUDE HEADER_FILE
  ;

function: TYPE IDENTIFIER '(' ')' '{' expression '}'
  ;

expression: RETURN NUMBER ';'   {
                                  /* char *str = (char *) malloc(50); // TODO better way to do this??
                                  memset(str, '\0', 50); */
                                  /* sprintf(str, "movl\t$%d, %%eax\n", yylval.num); */
                                  /* emit(str); */
                                  /* free(str); */
                                  fprintf(out, "\tmovl\t$%ld, %%eax\n", yylval.num);
                                }
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "error: %s\n", str);
}
