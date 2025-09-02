/*
    Author: Ryan Patrick
    Timestamp: 02-Sep-2025
    Purpose: Bison reads this file to generate a cycle notation parser
*/

%{
#include <iostream>
#include "cycle_notation_scanner.hpp"
#include "../Sym_cycle_notation_parser.hpp"
%}

%union {
	struct NumNode* n = nullptr;
	int i;
}

%token <i> NUMBER

%type <n> number_list
%type <i> cycle expression

%%
expression: /* nothing */
 | expression cycle { std::cout << $2 << "\n"; }
;

cycle: '(' number_list ')'	{ PrintNumNodeList($2); $$ = 5; }
;

number_list: /* nothing */
 | number_list NUMBER		{ $$ = AddNodeToTail($1, $2); }
;
%%

void yyerror(const char* s)
{
	std::cerr << "error: " << s << "\n";
}