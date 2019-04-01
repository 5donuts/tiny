%{
  #include "tiny.h"
%}

%token INCLUDE HEADER_FILE
%token TYPE IDENTIFIER RETURN NUMBER
%token OPEN_BRACE CLOSE_BRACE

%%

program: header function
  | function
  ;

header: INCLUDE HEADER_FILE
  ;

function: TYPE IDENTIFIER '(' ')' OPEN_BRACE expression CLOSE_BRACE
  ;

expression: RETURN NUMBER ';'
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "error: %s\n", str);
}
