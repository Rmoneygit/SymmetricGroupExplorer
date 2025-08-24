%option nounistd
%option never-interactive
%option main
%option c++

%{
using token = MC::MC_Parser::token;
%}

%%

[[:digit:]]+[[:space:]]+	{
								return(token::NUMBER);
							}

\(		{
			return(token::LEFT_PAREN);
		}
		
\)		{
			return(token::RIGHT_PAREN);
		}
%%