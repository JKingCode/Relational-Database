#ifndef Interpreter_H
#define Interpreter_H


#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include "datalog.h"
#include "Relation.h"
#include "Toople.h"
#include "Scheme.h"
#include "DatabaseRelation.h"
#include "Node.h"


using namespace std;

class Interpreter {
protected:
	bool tupAdded = false;
	int worthless;
	int postNum = 1;
	int passes = 0;
	stack<int> allPosts;
	datalog dave;
	string nam;
	string allRules = "Rule Evaluation";
	Scheme green;
	string totalQuer = "\n\nQuery Evaluation\n";
	DatabaseRelation everything;
	DatabaseRelation Queried;
	DatabaseRelation Ruled;
	list<int> porple;
	vector<int> worthlessToo;
	vector<int> postermister;
	vector<parameter> keep;
	vector<int> SCCGroup;
	map<string, int> stores;

	map<int, Node> graph;
	map<int, Node> reverseGraph;

public:
	Interpreter(datalog dats);

	void evalRules(vector<Rule> evaluatate);
	Relation eval1Rule(Rule toEval);
	Relation evalPredicate(Predicate toEval);
	Relation united(Relation old, Relation toAdd);

	string toString();
	string evalQueries();
	Relation eval1Quer(Predicate quer);

	//Relation select(Relation datas, string getem, int col);
	//Relation rename(Relation toChange, string changeTo, int col);
	//Relation project(Relation toChange, vector<string> toProject);

	void depGraph(vector<Rule> ruleList);
	void reverseDepGraph(map<int, Node> firstGraph);
	int DFSForest(int rulNum);
	int DFSForward(int rulNum);
	vector<vector<int>> SCC();


};





#endif