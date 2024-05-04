// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the type checking functions

#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <map>
#include <vector>


using namespace std;

#include "types.h"
#include "listing.h"

Types currentListType;

void checkAssignment(Types lValue, Types rValue, string message) {
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
}

Types checkWhen(Types true_, Types false_) {
	if (true_ == MISMATCH || false_ == MISMATCH)
		return MISMATCH;
	if (true_ != false_)
		appendError(GENERAL_SEMANTIC, "When Types Mismatch ");
	return true_;
}

Types checkSwitch(Types case_, Types when, Types other) {
	if (case_ != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Switch Expression Not Integer");
	return checkCases(when, other);
}

Types checkCases(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == NONE || left == right)
		return right;
	appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
	return MISMATCH;
}

Types checkArithmetic(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Integer Type Required");
	return MISMATCH;
}

// I dont know why the types are not being paseed properly to this, it has a 100% fail rate whenever 
// an arithmetic operator is encountered. I have tried multiple different ways
Types checkArithmeticType(Types left, Types right) {
    if (left == MISMATCH || right == MISMATCH) {
        return MISMATCH;
    }
    if ((left != INT_TYPE && left != REAL_TYPE) || (right != INT_TYPE && right != REAL_TYPE)) {
        return left;
    }
    appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
    return MISMATCH;

}

Types checkModIsInteger(Types left, Types right) {
    if (left != INT_TYPE || right != INT_TYPE) {
        appendError(GENERAL_SEMANTIC, "Remainder Operator Requires Integer Operands");
    }
    return INT_TYPE;
    
}

Types checkNegation(Types right) {
    if (right == MISMATCH || right != INT_TYPE || right != REAL_TYPE) {
        appendError(GENERAL_SEMANTIC,  "Arithmetic Operator Requires Numeric Types");
    };
    return right;
}

Types checkComparison(Types left, Types right) {
    if (left != right) {
        appendError(GENERAL_SEMANTIC, "Character Literals Cannot be Compared to Numeric Expressions");
    }
    if (left == MISMATCH || right == MISMATCH)
        return MISMATCH;
    return left;
}

bool isTypeValid(const vector<Types>* typesList, Types expectedType) {
    for (const auto& type : *typesList) {
        if (type != expectedType) {
            return false;
        }
    }
    return true;
}

double evaluateNegation(Types right) {
    return ~right;
}

Types getTypeOfExpression(double value) {
    if (floor(value) == value) {
        return INT_TYPE;
    }
    return REAL_TYPE;
}


char evaluateCharLiteral(const std::string& literal) {
    std::string value = literal.substr(1, literal.size() - 2);

    if (value.size() > 1 && value[0] == '\\') {
        switch (value[1]) {
            case 'n': return '\n';
            case 't': return '\t';
            default: return value[1];
        }
    }

    return value[0];
}

int hexToInt(const std::string& hexString) {
    std::stringstream ss;
    ss << std::hex << hexString;
    int decimal;
    ss >> decimal;
    return decimal;
}