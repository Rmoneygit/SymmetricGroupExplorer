%option nounistd noyywrap never-interactive nodefault

%{
#include "cycle_notation_parser.hpp"
%}

%%
"+" { printf("PLUS\n"); }
\n  { printf("NEWLINE\n"); }
.   { printf("Mystery character: %s\n", yytext); }
%%