#ifndef Scheme_H
#define Scheme_H



#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

class Scheme : public vector <string> {

protected:
	vector<string> shemes;


public:
	Scheme();
	Scheme(vector<string> schem);

};


#endif