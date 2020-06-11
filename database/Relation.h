#ifndef Relation_H
#define Relation_H


#include "Scheme.h"
#include "Toople.h"
#include <vector>
#include <set>
#include <map>
#include <string>

//using namespace std;

class Relation {

protected:
	vector<string> name;
	string names;
	Scheme schemes;
	set <Toople> tup;


public:
	Relation();
	Relation(string nam, Scheme schem, set<Toople> tups);
	Relation(string nam, Scheme schem);
	Relation(vector<string> nam);

	Relation select(string searchVal, int col);
	Relation select(string searchVal, int col1, int col2);
	//Relation select(string searchVal, vector<int> col);

	Relation rename(string renameVal, int col);
	Relation rename(vector <string> renameVal, vector <int> col);

	Relation project(vector<string> toProject);

	vector<string> getName();
	set <Toople> getTup();
	void addTuple(Toople toop);
	string toString();

	Relation join(Relation toJoin);
	bool isJoinable(Toople T1, Toople T2, vector<string> name1, vector<string> name2);
	Toople joinTuples(Toople T1, Toople T2, vector<string> name1, vector<string> name2);

	Relation join(Relation toJoin1, Relation toJoin2);
	vector<string> Uniter(Relation toUnite);


};


#endif
