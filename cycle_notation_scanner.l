/*
    Author: Ryan Patrick
    Timestamp: 02-Sep-2025
    Purpose: Flex reads this file to generate a cycle notation scanner
 */

%option noyywrap
%option nodefault
%option header-file="cycle_notation_scanner.hpp"

%{
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "cycle_notation_parser.hpp"
#include "../Sym_cycle_notation_parser.hpp"
%}

%%
"(" |
")"			{ return yytext[0]; }
[0-9]+		{ yylval.i = atoi(yytext); return NUMBER; }
[ \t]		{ /* Ignore whitespace */}
.			{ 
                std::ostringstream oss;
                oss << "Invalid character: \'" << *yytext << "\'.";
                throw std::exception(oss.str().c_str()); 
            }
%%
