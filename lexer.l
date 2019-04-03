%{
  #include "tiny.h"
%}

%option noyywrap

/* exclusive start condition for block comments */
%x BLOCK_COMMENT

%%

"//"[^\n]*          { /* Discard single-line comments */ }
"/*"                { BEGIN(BLOCK_COMMENT); } /* consume block comments */
<BLOCK_COMMENT>"*/" { BEGIN(INITIAL); }
<BLOCK_COMMENT>.    { }
<BLOCK_COMMENT>\n   { }
[ \t\n]+            { /* Ignore whitespace */ }

"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
";"             { return ';'; }
"-"             { return '-'; }
"~"             { return '~'; }
"!"             { return '!'; }

[0-9]+          { yylval.num = atol(yytext);
                  return NUMBER; }

"return"        { return RETURN; }

"int"           { /* TODO redo these to use symrec pointers instead of str */
                  /* yylval->str = malloc(strlen(yytext) + 1);
                  strcpy(yylval->str, yytext); */
                  return TYPE; }
"main"          { /* yylval->str = malloc(strlen(yytext) + 1);
                  strcpy(yylval->str, yytext); */
                  return IDENTIFIER; }

%%
