#ifndef Rule_H
#define Rule_H
//#pragma once

//#include "parser.h"
#include "Predicate.h"
//#include "datalog.h"
//#include "parameter.h"
//#include "expression.h"
#include "Token.h"
//#include "scanner.h"
#include <vector>
using namespace std;

class Rule{
protected:
	vector<Predicate> rules;
	Token colDash;
	Predicate header;
	Token period;

public:
	Rule(/*this will need arguments, but I'm not sure what yet. */);
	Rule(Predicate head, Token col, vector<Predicate> rulz, Token per);
	string toString();

	Predicate getHead();
	vector<Predicate> getRules();
};





#endif
