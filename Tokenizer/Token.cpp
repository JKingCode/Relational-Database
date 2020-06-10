

#include "Token.h"

Token::Token(tokenType t, string val, int num) {
	tok = t;
	value = val;
	lineNum = num;
}


string Token:: toString() {
	string returnable;
	string tokeName;
	//tok;

	switch (tok) {
	case COMMA: tokeName = "COMMA"; break;
	case PERIOD: tokeName = "PERIOD"; break;
	case Q_MARK: tokeName = "Q_MARK"; break;
	case LEFT_PAREN: tokeName = "LEFT_PAREN"; break;
	case RIGHT_PAREN: tokeName = "RIGHT_PAREN"; break;
	case COLON: tokeName = "COLON"; break;
	case COLON_DASH: tokeName = "COLON_DASH"; break;
	case MULTIPLY: tokeName = "MULTIPLY"; break;
	case ADD: tokeName = "ADD"; break;
	case SCHEMES: tokeName = "SCHEMES"; break;
	case FACTS: tokeName = "FACTS"; break;
	case RULES: tokeName = "RULES"; break;
	case QUERIES: tokeName = "QUERIES"; break;
	case ID: tokeName = "ID"; break;
	case STRING: tokeName = "STRING"; break;
	case COMMENT: tokeName = "COMMENT"; break;
	case UNDEFINED: tokeName = "UNDEFINED"; break;
	case endOF: tokeName = "EOF"; break;
	}

	returnable = "(" + tokeName /*figure out how to convert the enum to a string*/ + "," + "\"" + value + "\"" + "," + to_string(lineNum);
	return returnable;
}

string Token::getVal() {
	string returnable;
	returnable = value;
	return returnable;
}

string Token::getLine() {
	string returnable;
	returnable = to_string(lineNum);
	return returnable;
}


