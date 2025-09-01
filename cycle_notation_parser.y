%{
#include <iostream>
#include "cycle_notation_scanner.hpp"
int yylex();
void yyerror(const char* s);
%}

%token NUMBER
%token OP_PAREN CL_PAREN

%%
expression: /* nothing */
 | expression cycle { std::cout << $2 << "\n"; }
;

cycle: OP_PAREN number_list CL_PAREN
;

number_list: /* nothing */
 | number_list NUMBER
;
%%

void yyerror(const char* s)
{
	std::cerr << "error: " << s << "\n";
}