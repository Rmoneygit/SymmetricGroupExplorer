%option nounistd
%option never-interactive
%option main
%option c++

%{
#include <stdio.h>
%}

NUMBER [[:digit:]]+[[:space:]]+
CYCLE \({NUMBER}+\)

%%

{CYCLE}+ { printf("Found cycle: %s\n", yytext); }

%%