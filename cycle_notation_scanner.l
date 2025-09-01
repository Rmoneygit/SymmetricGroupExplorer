%option noyywrap
%option nodefault
%option header-file="cycle_notation_scanner.hpp"

%{
#include <iostream>
#include "cycle_notation_parser.hpp"
%}

%%
"("			{ std::cout << "OPENING PARENTHESIS\n"; return OP_PAREN; }
")"			{ std::cout << "CLOSING PARENTHESIS\n"; return CL_PAREN; }
[0-9]+		{ std::cout << "NUMBER\n"; return NUMBER; }
[ \t]		{ /* Ignore whitespace */}
.			{ std::cout << "Invalid character:" << yytext << "\n"; }
%%
