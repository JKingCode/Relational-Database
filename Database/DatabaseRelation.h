#ifndef DatabaseRelation_H
#define DatabaseRelation_H


#include "Scheme.h"
#include "Relation.h"
#include "Toople.h"
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

class DatabaseRelation : public map<string, Relation> {
protected:
	map<string, int> green;

	string name;
	Scheme headers;
	set<Toople> allData;
public:
	DatabaseRelation();
	//databaseRelation(string nam, scheme rel);
	DatabaseRelation(string nam, Scheme rel, set<Toople> tup);
	string toString();

};


#endif