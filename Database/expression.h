#ifndef expression_H
#define expression_H
//#pragma once

#include "parser.h"
#include "Predicate.h"
//#include "parameter.h"
#include <vector>

class expression {
protected:
	Token leftParen;
	parameter leftParam;
	Token Operator;
	parameter rightParam;
	Token rightParen;
public:
	expression();
	expression(Token lParen, parameter lParam, Token op, parameter rParam, Token rParen);
	string toString();
};




#endif
