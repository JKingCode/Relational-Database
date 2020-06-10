#ifndef scanner_H
#define scanner_H

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
using namespace std;


class scanner {
protected:

	map<tokenType, string> tokens;
	vector<Token> tokVec;
	char currentChar = ' ';
	tokenType currentToken;
	string value;
	int lineNumber = 1;
	int keepNumber = 0;
	ifstream in;
	string fullString = "";

public:
	scanner(string fileName);
	char Scan();
	string scanId(char curr);
	//string getaString();
	string getBlockComment();
	string printer();
	bool stringer(char current);
};

#endif
