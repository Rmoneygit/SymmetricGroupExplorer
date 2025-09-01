%{
#include <stdio.h>
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
	fprintf(stderr, "error: %s\n", s);
}