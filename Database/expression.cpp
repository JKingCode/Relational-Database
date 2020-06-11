
#include "expression.h"

expression:: expression(Token lParen, parameter lParam, Token op, parameter rParam, Token rParen) {
	leftParen = lParen;
	leftParam = lParam;
	Operator = op;
	rightParam = rParam;
	rightParen = rParen;
}

string expression::toString() {
	string returnable;
	returnable += leftParen.getVal();
	returnable += leftParam.toString();
	returnable += Operator.getVal();
	returnable += rightParam.toString();
	returnable += rightParen.getVal();
	return returnable;
}

