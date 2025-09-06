/*
    Author: Ryan Patrick
    Timestamp: 02-Sep-2025
    Purpose: Bison reads this file to generate a cycle notation parser
*/

%{
#include <iostream>
#include <stdexcept>
#include "cycle_notation_scanner.hpp"
#include "../Sym_cycle_notation_parser.hpp"
#include "../Sym_data_types.hpp"

/* Interface to the scanner*/
void yyerror(char* s);

%}

%code requires {
#include "../Sym_cycle_notation_parser.hpp"
#include "../Sym_data_types.hpp"
}

%union {
	struct Sym::NumNode* n = nullptr;
	int i;
	Sym::Permutation* p;
}

%token <i> NUMBER

%type <n> number_list
%type <i> expression
%type <p> cycle

%%
expression: /* nothing */
 | expression cycle { std::cout << "Hi\n"; }
;

cycle: '(' number_list ')'	{ $$ = Sym::CreatePermutation($2); }
;

number_list: /* nothing */
 | number_list NUMBER		{ $$ = Sym::AddNodeToTail($1, $2); }
;
%%

void yyerror(char* s)
{
	std::cout << "Error: " << s << "\n";
}