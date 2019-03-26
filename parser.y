%{
  #include <stdio.h>

  // function declarations
  int yylex();
  void yyerror(char *s);
%}

%token INCLUDE HEADER_FILE
%token TYPE IDENTIFIER RETURN INT
%token OPEN_BRACE CLOSE_BRACE

%%

program:
  header function
  | function
  ;

header:
  INCLUDE HEADER_FILE
  ;

function:
  TYPE IDENTIFIER '(' ')' OPEN_BRACE expression CLOSE_BRACE
  ;

expression:
  RETURN INT ';'
  ;

%%

void yyerror(char *str) {
  fprintf(stderr, "error: %s\n", str);
}
