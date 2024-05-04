/* CMSC 430 Compiler Theory and Design
   Project 4 Skeleton
   UMGC CITE
   Summer 2023
   
   Project 4 Parser with semantic actions for static semantic errors */

%{
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
Types find(Symbols<Types>& table, CharPtr identifier, string tableName);
void yyerror(const char* message);

Symbols<Types> scalars;
Symbols<Types> lists;

extern Types currentListType;

%}

%define parse.error verbose

%union {
	CharPtr iden;
	Types type;
	Operators oper;
	double value;
	vector<double>* values;
	vector<double>* list;
	vector<Types>* typesList;
}

%token <iden> IDENTIFIER

%token <type> INT_LITERAL CHAR_LITERAL REAL_LITERAL HEX_INT_LITERAL

%token <oper> OROP      /* | */
%token <oper> ANDOP     /* & */
%token <oper> RELOP   /* <, >, <>, == */
%token <oper> ADDOP     /* + */
%token <oper> MULOP     /* * */
%token <oper> MODOP     /* % */
%token <oper> XOROP     /* ^ */
%token <oper> NEGOP  /* ~ */
%token <oper> NOTOP     /* ! */
%token <oper> ARROW   /* => */

%token FOLD ENDFOLD LEFT RIGHT

%token BEGIN_ CASE CHARACTER ELSE END ENDSWITCH FUNCTION INTEGER IS LIST OF OTHERS
	RETURNS SWITCH WHEN

%token IF ELSIF ENDIF THEN


%type <type> list expressions body type statement_ statement cases case expression
	term primary relation condition optional_elsif_else statements

%type <value> optional_variable fold_direction

%%

function:	
	function_header variables optional_variable body ;

variables:
	variable variables |
	%empty;
	
		
function_header:	
	FUNCTION IDENTIFIER RETURNS type ';' ;

type:
	INTEGER {$$ = INT_TYPE;} |
	CHARACTER {$$ = CHAR_TYPE; } |
	REAL_LITERAL {$$ = REAL_TYPE;} |
	IDENTIFIER;
	
optional_variable:
	variable |
	%empty;
    
variable:	
	IDENTIFIER ':' type IS statement ';' {checkAssignment($3, $5, "Variable Initialization"); scalars.insert($1, $3);} |
    IDENTIFIER ':' LIST OF type IS list ';' {lists.insert($1, $5); currentListType = $5;} ; 

list:
    '(' expressions ')' {$$ = $2;} ;

expressions:
    expressions ',' expression {$$ = getTypeOfExpression($1);}; | 
	expression {$$ = getTypeOfExpression($1);};

body:
	BEGIN_ statement_ END ';' {$$ = $2;} ;
    
statement_:
	statement ';' |
	error ';' {$$ = MISMATCH;} ;
	
statement:
	expression {} |
	WHEN condition ',' expression ':' expression 
		{$$ = checkWhen($4, $6);} |
	IF condition THEN statements optional_elsif_else ENDIF {$$ = $5;} |
	    FOLD fold_direction ADDOP expression ENDFOLD |
	SWITCH expression IS cases OTHERS ARROW statement ';' ENDSWITCH 
		{$$ = checkSwitch($2, $4, $7);} ;

fold_direction:
    LEFT { $$ = 1; } | 
    RIGHT { $$ = -1; }; 

/* arithmetic_operator:
    ADDOP |
    MULOP |
    MODOP |
	XOROP; */


optional_elsif_else:
    ELSIF condition THEN statements optional_elsif_else { $$ = $2 ? $4 : $5; } |
    ELSE statements { $$ = $2; } |
    %empty;
		
statements:
    statement ';' statements { $$ = $1; } | 
    statement ';' { $$ = $1; };

cases:
	cases case {$$ = checkCases($1, $2);} |
	%empty {$$ = NONE;} ;
	
case:
	CASE INT_LITERAL ARROW statement ';' {$$ = $4;} ; 

condition:
	condition ANDOP relation |
	condition OROP relation |
	primary |
	relation ;

relation:
	'(' condition ')' {$$ = $2;} |
	expression RELOP expression {$$ = checkComparison($1, $3);} |
	expression ANDOP expression {$$ = checkComparison($1, $3);} |
	expression OROP expression {$$ = checkComparison($1, $3);}; 
	
expression:
	expression XOROP term {$$ = checkArithmetic($1, $3); checkArithmeticType($1, $3);} |
	expression ADDOP term {$$ = checkArithmetic($1, $3); checkArithmeticType($1, $3);} |
	expression MODOP term {$$ = checkArithmetic($1, $3); checkModIsInteger($1, $3);} |
	term ;
      
term:
	term MULOP primary {$$ = checkArithmetic($1, $3);} |
	primary ;

primary:
	'(' expression ')' {$$ = $2;} |
	HEX_INT_LITERAL |
	INT_LITERAL | 
	REAL_LITERAL |
	CHAR_LITERAL |
	NEGOP primary {$$ = checkNegation($2);} |
	IDENTIFIER '(' expression ')' {$$ = find(lists, $1, "List");} |
	IDENTIFIER  {$$ = find(scalars, $1, "Scalar");} ;


%%

Types find(Symbols<Types>& table, CharPtr identifier, string tableName) {
	Types type;
	if (!table.find(identifier, type)) {
		appendError(UNDECLARED, tableName + " " + identifier);
		return MISMATCH;
	}
	return type;
}

void yyerror(const char* message) {
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[]) {
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
