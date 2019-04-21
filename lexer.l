%{
  #include <stdlib.h> // atol, malloc, free, etc.
  #include <stdio.h>

  #include "symtab.h" // for symrec *lookup(char *)
  #include "parser.tab.h" // parser token definitions

  void yyerror(char *);
%}

%option yylineno
%option noyywrap

/* exclusive start condition for block comments */
%x BLOCK_COMMENT

IDENTIFIER [a-zA-Z][a-zA-Z0-9]*

%%

"//"[^\n]*          { /* Ignore single-line comments */ }
"/*"                { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/" { BEGIN(INITIAL); }
<BLOCK_COMMENT>.    { /* Ignore block comments */ }
<BLOCK_COMMENT>\n   { }
[ \t\r\n]+          { /* Ignore whitespace */ }
<<EOF>>             { return END; }

"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
";"             { return ';'; }
"~"             { return '~'; }
"!"             { return '!'; }
"+"
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }

[0-9]+          { yylval.num = atol(yytext);
                  return NUMBER;
                }

"return"        { return RETURN; }

"int"           { yylval.val_type = INT;
                  return TYPE;
                }
"void"          { yylval.val_type = VOID;
                  return TYPE;
                }

{IDENTIFIER}    { yylval.symbol = lookup(yytext);
                  return IDENTIFIER;
                }

%%
