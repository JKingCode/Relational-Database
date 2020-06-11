#ifndef Toople_H
#define Toople_H

#include "Token.h"
#include <string>
#include <vector>


using namespace std;

class Toople : public vector <string> {

protected:
	vector<string> name;


public:
	Toople();
	//string getString();
};


#endif