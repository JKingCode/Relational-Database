
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
			returnable += "=" + toop[i] + ",";
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

Relation Relation::rename(vector <string> renameVal, vector <int> col) {

	for (unsigned int i = 0; i < name.size(); i++) {
		//cout << name[i] << " ";
		//cout << renameVal[i] << " ";
	}

	Relation renamed;
	vector<string> newName;
	newName = name;

	for (unsigned int i = 0; i < renameVal.size(); i++) {
		//we are hittin some issues here.
		//cout << renameVal[i] << " " << name[i] << " ";
		name[i] = renameVal[i];
	}
	//to troubleshoot this you could print name here
	renamed = Relation(newName);
	vector<Toople> transfer;

	for (Toople t: tup) {
		renamed.addTuple(t);
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
	if (tup.size() == 0) {
		return returnable;
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

Relation Relation::join(Relation toJoin){
	//combining the two schemes
	vector <string> S = name;
	for(unsigned int  i = 0; i < toJoin.getName().size(); i++){
		bool canAdd = true;
		for(unsigned int j = 0; j < name.size(); j++){
				if(toJoin.getName()[i] == name[j]){
					canAdd = false;
				}
		}
		if(canAdd){
			S.push_back(toJoin.getName()[i]);
		}
	}

for(Toople temp: tup){
	//cout << "tup tuples " << endl;
	for(unsigned int i = 0; i < temp.size(); i++){
		string garbage = temp[i];
		//cout << garbage << " ";
	}
}




	Relation joined = Relation(S);
	for(Toople one: tup){
		for(Toople two: toJoin.getTup()){
			if(isJoinable(one, two, name, toJoin.getName())){
				joined.addTuple(joinTuples(one,two,name, toJoin.getName()));
			}
		}
	}


return joined;
}

bool Relation:: isJoinable(Toople T1, Toople T2, vector<string> name1, vector<string> name2){
	for(unsigned int i = 0; i < name1.size(); i++){
		for(unsigned int j = 0; j < name2.size(); j++){
			if((name1[i] == name2[j]) && (T1[i] != T2[j])){
				//cout << endl << "not joinin " << name1[i] << endl;
				return false;
			}
		}
	}

	return true;
}

Toople Relation :: joinTuples(Toople T1, Toople T2, vector<string> name1, vector<string> name2){
	Toople temp = T1;

	for(unsigned int i = 0; i < name2.size(); i++){
		bool canAdd = true;
		for(unsigned int j = 0; j < name1.size(); j++){
			if(name1[j] == name2[i]){
				//cout << endl << name2[i] << " addin them tuples " << T2[i] << endl;
				canAdd = false;
			}
		}
		if(canAdd){
			temp.push_back(T2[i]);
		}
	}

	return temp;
}

Relation Relation::join(Relation toJoin1,Relation toJoin2) {
	// could go through and change to pass just one relation fairly easily
	Relation toReturn = Relation(name);
	vector<int> sameIndex1;
	vector<int> sameIndex2;

	//finding the
	for (unsigned int i = 0; i < toJoin1.getName().size(); i++) {
		for (unsigned int j = 0; j < toJoin2.getName().size(); j++) {
			if (toJoin1.getName()[i] == toJoin2.getName()[j]) {
				sameIndex1.push_back(i);

				sameIndex2.push_back(j);
				//ask someone about these errors.
			}
		}
	}

	//trying to join the two tuples
	for (Toople search1 : toJoin1.getTup()) {
		for (Toople search2 : toJoin2.getTup()) {
			bool canAdd = true;
			vector<string> tup1 = search1;
			vector<string> tup2 = search2;
			//checking to see if the tuple values are equal
			for (unsigned int i = 0; i < sameIndex1.size(); i++) {
				if (tup1[sameIndex1[i]] == tup2[sameIndex2[i]]) {
					canAdd = true;
				}
				else {
					canAdd = false;
				}
			}
			//adding tuples to the relation
			if (canAdd == true) {
				Toople toAdd = search1;
				for (unsigned int i = 0; i < search2.size(); i++) {
					bool skip = false;
					for (unsigned int j = 0; j < sameIndex2.size(); j++) {
						int junk = i;
						if (junk == sameIndex2[j]) {
							skip = true;
						}
					}
					if (skip) {
						continue;
					}
					else {
						toAdd.push_back(search2[i]);
					}
				}
				addTuple(toAdd);

			}
		}
	}

	return toReturn;


}

vector<string> Relation::Uniter(Relation toUnite) {
	
	vector<string> added;
	//cout << endl << "tuples added:" << name.size();
	for (Toople toop : toUnite.getTup()) {
		int checker = tup.size();

		addTuple(toop);
		int doubleChecker = tup.size();

		if (checker != doubleChecker) {
			added.push_back("\n  ");
			//cout << endl;
			for (unsigned int i = 0; i < toop.size(); i++) {
				//cout << toop[i] << " ";
				added.push_back(name[i]);
				added.push_back("=");
				added.push_back(toop[i]);
				added.push_back(", ");
			}
			added.pop_back();
		}

	}


	return added;
}

/*
vector<string> Relation::Uniter(Relation toUnite) {
	
	vector <string> added;
	for (Toople toop : toUnite.getTup()) {
		added.push_back("  ");
		for (unsigned int i = 0; i < toop.size(); i++) {
			added.push_back(name[i]);
			added.push_back("=");
			added.push_back(toop[i]);
			added.push_back(", ");
		}
		added.pop_back();
		added.push_back("\n");

		addTuple(toop);
	}
	//Relation returnable = Relation(name);

	return added;
}
*/
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
