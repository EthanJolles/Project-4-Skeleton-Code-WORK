// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;


void yyerror(const char* message);


enum Operators {ADD, SUB, MULTIPLY, DIVIDE, LESS, EQUALS, LESSTHANEQUAL, AND, EXPONENT, NEGATE, MODULO, XOR, NOT, NOTEQUAL, GREATER, GREATERTHANEQUAL, ASSIGN, OR};
enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, BOOL_TYPE, NONE};

extern Types currentListType;

void checkAssignment(Types lValue, Types rValue, string message);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkArithmetic(Types left, Types right);
char evaluateCharLiteral(const std::string& literal);


int hexToInt(const std::string& hexString);

bool checkListTypes(const vector<Types>* typesList, Types expectedType);
Types getTypeOfExpression(double value);

