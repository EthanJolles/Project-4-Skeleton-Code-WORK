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
    if (lValue == INT_TYPE && (rValue == MISMATCH || rValue == REAL_TYPE)) {
        appendError(GENERAL_SEMANTIC, "Narrowing " + message);
        return;
    }
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

Types checkIfMatch(Types statement, Types expectedType) {
    if (statement != expectedType) {
        appendError(GENERAL_SEMANTIC, "If-Elsif-Else Type Mismatch");
        return MISMATCH;
    }
    return expectedType;
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
    if (left == INT_TYPE && right == INT_TYPE) {
        return INT_TYPE;
    }
    if ((left == INT_TYPE && right == REAL_TYPE) || (left == REAL_TYPE && right == INT_TYPE)) {
        return REAL_TYPE;
    }
    if ((left != INT_TYPE && left != REAL_TYPE) || (right != INT_TYPE && right != REAL_TYPE)) {
        appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types");
        return left;
    }
            printf("Womp2");
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

bool checkFoldNumericList(const vector<Types>* typesList) {
    // Check if the pointer is null before dereferencing
    if (typesList == nullptr) {
        appendError(GENERAL_SEMANTIC, "Null pointer passed to checkFoldNumericList");
        return false;
    }

    // Iterate through the list and check each type
    for (Types type : *typesList) {
        if (type != INT_TYPE && type != REAL_TYPE) {
            appendError(GENERAL_SEMANTIC, "Fold Requires A Numeric List");
            return false;
        };
    }
    return true;
}

double evaluateNegation(Types right) {
    return ~right;
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

int hexToInt(const char* hexStr) {
    int num;
    sscanf(hexStr + 1, "%x", &num); // Skip the '#' character
    return num;
}

// Utility function for debugging
void printTypeName(Types type) {
    printf("\nReceived Type: ");
    switch (type) {
        case MISMATCH:
            printf("MISMATCH\n");
            break;
        case INT_TYPE:
            printf("INT_TYPE\n");
            break;
        case CHAR_TYPE:
            printf("CHAR_TYPE\n");
            break;
        case REAL_TYPE:
            printf("REAL_TYPE\n");
            break;
        case BOOL_TYPE:
            printf("BOOL_TYPE\n");
            break;
        case NONE:
            printf("NONE\n");
            break;
        default:
            printf("UNKNOWN_TYPE\n");
    }
}