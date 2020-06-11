#ifndef Token_H
#define Token_H


#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>
#include <stdlib.h>
using namespace std;

enum tokenType {
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	UNDEFINED,
	endOF,

};

class Token{
protected:
	tokenType tok;
	string value = "";
	int lineNum = 0;

public:
	Token();
	Token(tokenType t, string val, int num);
	string toString();
	string getVal();
	string getLine();
	tokenType getType();
};

#endif
