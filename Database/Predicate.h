#ifndef PREDICATE_H
#define PREDICATE_H
//#pragma once

//#include "parser.h"
#include "Parameter.h"
#include "Token.h"
//#include "expression.h"
//#include "Rule.h"
#include <vector>
#include <string>
using namespace std;

class Predicate {
protected:
	vector<string> predicates;
	Token iD;
	Token leftPar;
	vector<parameter> params;
	Token rightPar;
	vector<Token> ids;
	bool head = false;
public:
	Predicate();
	Predicate(Token id, Token lPar,vector<parameter> paraList, Token rPar);
	Predicate(Token id, Token lPar, vector<Token> paraList, Token rPar);
	string toString();
	vector<Token> getIDs();
	vector<parameter> getParams();

	Token getID();
};



#endif
