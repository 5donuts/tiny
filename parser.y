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

program: function
  ;

function: TYPE IDENTIFIER '(' ')' '{' statement '}'
  ;

statement: RETURN expression ';'  { // TODO change this to work for things besides main()
                                    int exit_code = $2;
                                    syscall call;
                                    call.code = SYS_EXIT;
                                    call.arg1 = &exit_code;
                                    make_syscall(&call);
                                  }
  ;

expression: NUMBER      { $$ = $1; }
  | '-' NUMBER          { $$ = -$2; } /* TODO change these to produce the relevant assembly instructions instead */
  | '~' NUMBER          { $$ = ~$2; }
  | '!' NUMBER          { $$ = !$2; }
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "Error | Line: %d\n\t%s\n", yylineno, str);
}
