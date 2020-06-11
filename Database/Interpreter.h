#ifndef Interpreter_H
#define Interpreter_H


#include <vector>
#include <set>
#include <map>
#include <string>

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include "datalog.h"
#include "Relation.h"
#include "Toople.h"
#include "Scheme.h"
#include "DatabaseRelation.h"


using namespace std;

class Interpreter {
protected:
	datalog dave;
	string nam;
	Scheme green;
	string totalQuer;
	DatabaseRelation everything;
	DatabaseRelation Queried;
	vector<parameter> keep;
	map<string, int> stores;

public:
	Interpreter(datalog dats);

	string toString();
	string evalQueries();
	Relation eval1Quer(Predicate quer);

	Relation select(Relation datas, string getem, int col);
	Relation rename(Relation toChange, string changeTo, int col);
	Relation project(Relation toChange, vector<string> toProject);


};





#endif