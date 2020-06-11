
#include "Relation.h"
#include <string>

Relation::Relation() {

}

Relation::Relation(string nam, Scheme schem) {
	names = nam;
	schemes = schem;
}

Relation::Relation(vector<string> nam) {
	name = nam;
}

string Relation::toString() {
	string returnable;
	//int i = 0;
	//cout << name.size() << endl;
	for (Toople toop : tup) {

		for (unsigned int i = 0; i < name.size(); i++) {
			returnable += "  " + name[i];
			returnable += "=";
			//cout << toop[i] << endl;
			returnable += toop[i];
			returnable += ", ";
		}
		returnable.pop_back();
		returnable.pop_back();

		returnable += "\n";
	}
	//cout << tup.size();
	return returnable;
}


Relation Relation:: select(string searchVal, int col) {
	Relation selected = Relation(name);

	for (set<Toople>::iterator it = tup.begin(); it != tup.end(); ++it) {
		vector <string> looks = *it;
		if (looks[col] == searchVal) {
			selected.addTuple(*it);
		}
	}
	return selected;
}

Relation Relation:: select(string searchVal, int col1, int col2) {
	Relation selected = Relation(name);

	for (Toople it : tup) {
		//cout << "stuck here" << endl;
		vector <string> looks = it;
		if (looks[col1] == looks[col2]) {
			selected.addTuple(it);
		}
	}
	return selected;
}

/*
Relation Relation::select(string searchVal, vector<int> col) {
	Relation selected = Relation(name);

	for (set<Toople>::iterator it = tup.begin(); it != tup.end(); ++it) {
		vector <string> looks = *it;
		bool canAdd = false;
		for (int i = 0; i < col.size(); i++) {

			if (looks[col[i]] == searchVal) {
				canAdd = true;
			}
			else {
				canAdd = false;
			}
		}
		if (canAdd) {
			selected.addTuple(*it);
		}

	}
	return selected;
}
*/

Relation Relation::rename(string renameVal, int col) {

	Relation renamed;
	vector<string> newName;
	newName = name;


	replace(newName.begin(), newName.end(), name[col], renameVal);
	//to troubleshoot this you could print name here
	renamed = Relation(newName);
	vector<Toople> transfer;

	for (set<Toople>::iterator it = tup.begin(); it != tup.end(); ++it) {
		renamed.addTuple(*it);
	}
	return renamed;

}

Relation Relation::project(vector<string> toProject) {
	Relation returnable;
	returnable = Relation(toProject);
	set<Toople> transfer = tup;
	//int counter = 0;
	//getting which columns to print out
	vector<int> colNum;
	for (unsigned int j = 0; j < toProject.size(); j++) {
		for (unsigned int i = 0; i < name.size(); i++) {
			if (toProject[j] == name[i]) {
				colNum.push_back(i);
			}
		}
	}


	for (Toople toop : tup) {
		Toople toPush;
		for (unsigned int i = 0; i < colNum.size(); i++) {
			toPush.push_back(toop[colNum[i]]);
		}
		returnable.addTuple(toPush);
	}


	return returnable;
}

void Relation::addTuple(Toople toop) {
	tup.insert(toop);
}
vector <string> Relation:: getName() {
	return name;
}

set <Toople> Relation:: getTup() {
	return tup;
}

/*
for(

data[name] = relation r; //schemes
data.at(name).add( toople); //facts
relation data();

for(pair<string, relation> p; data){
	p.first
	p.second
}

*/
