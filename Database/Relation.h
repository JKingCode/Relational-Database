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

	Relation project(vector<string> toProject);

	vector<string> getName();
	set <Toople> getTup();
	void addTuple(Toople toop);
	string toString();




};


#endif