//#ifndef PARAMETER_H
//#define PARAMETER_H
#pragma once


//#include "parser.h"
//#include "expression.h"
#include "Token.h"
#include <vector>
//#include <stdexcept>
using namespace std;

class parameter {
protected:
	vector<string> parameters;//not using
	string para;
	Token param;
	string paramEx;

	bool isConst;

	bool isTok = false;
	bool isEx = false;
public:
	parameter();
	parameter(Token paramTok);
	parameter(string express);
	string toString();
	bool getConst();

};



//#endif
