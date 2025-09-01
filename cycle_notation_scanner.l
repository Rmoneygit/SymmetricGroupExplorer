%option noyywrap
%option nodefault
%option header-file="cycle_notation_scanner.hpp"

%{
#include "cycle_notation_parser.hpp"
%}

%%
"+" { printf("PLUS\n"); }
\n  { printf("NEWLINE\n"); }
.   { printf("Mystery character: %s\n", yytext); }
%%
