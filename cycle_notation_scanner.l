/*
    Author: Ryan Patrick
    Timestamp: 02-Sep-2025
    Purpose: Flex reads this file to generate a cycle notation scanner
 */

%option noyywrap
%option nodefault
%option header-file="cycle_notation_scanner.hpp"

%{
#include <cstdio>
#include <cstdlib>
#include "cycle_notation_parser.hpp"
void yyerror(const char* s);
%}

%%
"(" |
")"			{ return yytext[0]; }
[0-9]+		{ yylval.i = atoi(yytext); return NUMBER; }
[ \t]		{ /* Ignore whitespace */}
.			{ 
				char message[50];
				sprintf(message, "Invalid character: %c\n", *yytext);
				yyerror(message);
			}
%%
