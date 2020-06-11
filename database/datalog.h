#ifndef datalog_H
#define datalog_H

//#include "parser.h"
//#include "parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include <vector>
#include <set>

class datalog {
protected:
	vector<Token> schemes;
	vector<Token> facts;
	vector<Predicate> queries;
	vector<Rule> rules;
	set<string> domains;
public:
	datalog(/*feed me arguments*/);
	datalog(vector<Token> schem, vector<Token> fac, vector<Rule> rul, vector<Predicate> quer);
	string toString();

	vector<Token> getSchemes();
	vector<Token> getFacts();
	vector<Rule> getRules();
	vector<Predicate> getQueries();
};



#endif