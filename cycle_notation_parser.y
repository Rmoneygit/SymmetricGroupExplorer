/*
    Author: Ryan Patrick
    Timestamp: 02-Sep-2025
    Purpose: Bison reads this file to generate a cycle notation parser
*/

%{
#include <iostream>
#include "cycle_notation_scanner.hpp"
#include "../Sym_cycle_notation_parser.hpp"
#include "../Sym_data_types.hpp"
#include "../Sym_symmetric_group.hpp"

/* Interface to the scanner*/
void yyerror(Sym::Permutation&, char* s);

%}

%code requires {
#include "../Sym_cycle_notation_parser.hpp"
#include "../Sym_data_types.hpp"
}

%parse-param { Sym::Permutation& result }

%union {
	struct Sym::NumNode* n = nullptr;
	int i;
	Sym::Permutation* p;
	Sym::PermutationVector* pv;
}

%token <i> NUMBER

%type <n> number_list
%type <pv> cycle_list
%type <p> cycle expression

%%
expression: cycle_list { 
							result = Sym::ComposePermutations(*$1);
							delete $1;
							$1 = nullptr;
					   }

cycle_list:
 | cycle_list cycle { 
						$$ = Sym::AddCycleToTail($1, $2);
					}
;

cycle: '(' number_list ')'	{ 
								$$ = Sym::CreatePermutation($2); 
								Sym::FreeNumNodeList($2); 
								$2 = nullptr;
							}
;

number_list: /* nothing */
 | number_list NUMBER		{ 
								$$ = Sym::AddNodeToTail($1, $2);
								Sym::PrintNumNodeList($1); 
							}
;
%%

void yyerror(Sym::Permutation& p, char* s)
{
	std::cout << "Error: " << s << "\n";
}