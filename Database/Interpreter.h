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
	bool tupAdded = false;
	datalog dave;
	string nam;
	string allRules = "Rule Evaluation";
	Scheme green;
	string totalQuer = "Query Evaluation\n";
	DatabaseRelation everything;
	DatabaseRelation Queried;
	DatabaseRelation Ruled;
	vector<parameter> keep;
	map<string, int> stores;

public:
	Interpreter(datalog dats);

	void evalRules(vector<Rule> evaluatate);
	Relation eval1Rule(Rule toEval);
	Relation evalPredicate(Predicate toEval);
	Relation united(Relation old, Relation toAdd);

	string toString();
	string evalQueries();
	Relation eval1Quer(Predicate quer);

	Relation select(Relation datas, string getem, int col);
	Relation rename(Relation toChange, string changeTo, int col);
	Relation project(Relation toChange, vector<string> toProject);


};





#endif