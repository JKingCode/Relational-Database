#ifndef parser_H
#define parser_H


#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <cstdlib>
#include <array>
#include <stack>
#include <stdexcept>
#include "Token.h"
//#include "scanner.h"
#include "Parameter.h"
#include "expression.h"
#include "datalog.h"
#include "Rule.h"
using namespace std;


class parser {
protected:
	datalog total;


	vector<Token> scanned;
	int location = 0;
	set <string> domain;
	Token bad;

	vector<Token> idVec;
	vector<Token> stringVec;

	vector<parameter> paraVec;
	vector<Token> expressVec;
public:
	bool success = true;

	parser(vector<Token> toParse);
	datalog datalogParse(Token currentToken);
	vector<Token> schemeList(Token currentToken);
	vector<Token> factList(Token currentToken);
	vector<Rule> ruleList(Token currentToken);
	vector<Predicate> queryList(Token currentToken);

	vector<Token> scheme(Token currentToken);
	vector<Token> fact(Token currentToken);
	Rule rule(Token currentToken);
	Predicate query(Token currentToken);

	Predicate headPredicate(Token currentToken);
	Predicate predicate(Token currentToken);

	vector<Predicate> predicateList(Token currentToken);
	vector<parameter> parameterList(Token currentToken);
	vector<Token> stringList(Token currentToken);
	vector<Token> idList(Token currentToken);

	parameter Parameter(Token currentToken);
	string express(Token currentToken);
	Token Operator(Token currentToken);


	//temporarily here until I find a better place
	Token match(tokenType currentToken);
	void error(Token token);

	datalog getTotal();
};




#endif

// put try catch in the main file

/*
void match(tokentype t){
	check if current token has that type.
	if(currentToken == t); //if they are the same type. So if they are both string, etc.
	if it does, advance to next token.
	if not, throw current token //error();

}

for grammars with ors

if(currentToken == +){
	match(add);
if(currentToken == *){
	match(multiply)
}
else{
error();
}




for lambda else{}. Lo an empty else



Parser:
token currentToken;
parser functions
vector<token>
datalogProgram datalog;

can have a vector of parameters in the predicate class. Store everything in parameter as a string
Rules have head predicate, and then body predicates (store body in vector of predicates. )

parameter
string value
string type

datalog program
//
vector<predicate> schemes
					facts
					quiries
vector<rules>

object of this lab is to have datalog program filled populated with what you need.

//most people don't pass off for nested expressions

Domain is all strings in facts. Store all strings in facts in a vector of strings
Domain is alphabetized, and there are no duplicates. Put strings in set to help with that.

*/
