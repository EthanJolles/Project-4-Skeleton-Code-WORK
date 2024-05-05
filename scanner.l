/* CMSC 430 Compiler Theory and Design
   Project 4 Skeleton
   UMGC CITE
   Summer 2023 */

/* This file contains flex input file */

%{
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"
#include "tokens.h"

%}

%option noyywrap

ws		[ \t\r]+
comment		\-\-.*\n
comment2	\/\/.*\n
line		[\n]
id		[A-Za-z]([A-Za-z0-9])*
digit		[0-9]
dec		{digit}+
char		'.'
char_literal    "'"([^'\\]|\\.)*"'"
punc		[,/\\(\)':;.#]
hex #[0-9A-Fa-f]+ 
real [0-9]+(\.[0-9]+)?(E[+-]?[0-9]+)?
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine();}
{comment2}	{ ECHO; nextLine();}
{line}		{ ECHO; nextLine(); }


"+"		{ ECHO; yylval.oper = ADD; return(ADDOP); }
"-"      { ECHO; yylval.oper = SUB; return(ADDOP); }
"*"		{ ECHO; yylval.oper = MULTIPLY; return(MULOP); }
"&"		{ ECHO; yylval.oper = AND; return(ANDOP); }
"=>"		{ ECHO; return(ARROW); }
"/"      { ECHO; yylval.oper = DIVIDE; return(MULOP); }
"%"      { ECHO; yylval.oper = MODULO; return(MODOP); }
"~"      { ECHO; yylval.oper = NEGATE; return(NEGOP); }
"^"      { ECHO; yylval.oper = XOR; return(XOROP); }
"<"		{ ECHO; yylval.oper = LESS; return(RELOP); }
"<="      { ECHO; yylval.oper = LESSTHANEQUAL; return(RELOP); }
">"      { ECHO; yylval.oper = GREATER; return(RELOP); }
">="      { ECHO; yylval.oper = GREATERTHANEQUAL; return(RELOP); }
"<>"     {ECHO; yylval.oper = NOTEQUAL; return(RELOP);}
"="      { ECHO; yylval.oper = EQUALS; return(RELOP); }
"!"      { ECHO; yylval.oper = NOT; return(NOTOP); }
"|"      { ECHO; yylval.oper = OR; return(OROP); }

if		{ ECHO; return(IF); }
else  { ECHO; return(ELSE); }
elsif { ECHO; return(ELSIF); }
endif { ECHO; return(ENDIF); }
fold        { ECHO; return FOLD; }
endfold { ECHO; return ENDFOLD; }
left {ECHO; return LEFT; }
right {ECHO; return RIGHT; }
begin		{ ECHO; return(BEGIN_); }
case		{ ECHO; return(CASE); }
then { ECHO; return(THEN);}
character	{ ECHO; return(CHARACTER); }
end		{ ECHO; return(END); }
endswitch	{ ECHO; return(ENDSWITCH); }
function	{ ECHO; return(FUNCTION); }
is		{ ECHO; return(IS); }
list		{ ECHO; return(LIST); }
of		{ ECHO; return(OF); }
others		{ ECHO; return(OTHERS); }
returns		{ ECHO; return(RETURNS); }
switch		{ ECHO; return(SWITCH); }
when		{ ECHO; return(WHEN); }

integer {ECHO; return(INTEGER); }
real {ECHO; return(REAL_LITERAL); }
character {ECHO; return(CHAR_LITERAL); }




{id}		{ ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); strcpy(yylval.iden, yytext); return(IDENTIFIER);}
{dec}		{ ECHO; yylval.value = atoi(yytext); return(INT_LITERAL); }
{char}		{ ECHO; yylval.type = CHAR_TYPE; return(CHAR_LITERAL); }
{char_literal} {ECHO; yylval.value = evaluateCharLiteral(yytext); return CHAR_LITERAL; }
{real}		{ ECHO; yylval.value = atof(yytext); return(REAL_LITERAL); }
{hex} { ECHO; yylval.value = hexToInt(yytext); return(HEX_INT_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.		{ ECHO; appendError(LEXICAL, yytext); }
%%
