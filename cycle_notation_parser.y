%{
#include <iostream>
#include "cycle_notation_scanner.hpp"
int yylex();
void yyerror(const char* s);
%}

%token NUMBER

%%
term: NUMBER
;
%%

void yyerror(const char* s)
{
	std::cerr << "error: " << s << std::endl;
}