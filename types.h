// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023
// Ethan Jolles

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;


void yyerror(const char* message);


enum Operators {ADD, SUB, MULTIPLY, DIVIDE, LESS, EQUALS, LESSTHANEQUAL, AND, EXPONENT, NEGATE, MODULO, XOR, NOT, NOTEQUAL, GREATER, GREATERTHANEQUAL, ASSIGN, OR};
enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, BOOL_TYPE, NONE};

double evaluateNegation(Types right);
int hexToInt(const char* hexStr);
char evaluateCharLiteral(const std::string& literal);

void checkAssignment(Types lValue, Types rValue, string message);
void printTypeName(Types type);
Types checkIfMatch(Types statement, Types expectedType);
Types checkOperatorMatch(Types lValue, Types rValue);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkArithmetic(Types left, Types right);
Types checkArithmeticType(Types left, Types right);
Types checkNegation(Types right);
Types checkFoldMatch(Types type);
void checkIsInt(Types type);
Types checkListMatch(Types type, Types expectedType);
Types checkModIsInteger(Types left, Types right);
Types checkComparison(Types left, Types right);
Types getTypeOfExpression(double value);

