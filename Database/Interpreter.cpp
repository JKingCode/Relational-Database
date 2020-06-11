

#include "Interpreter.h"
//#include "toople.h"

Interpreter::Interpreter(datalog dats) {

	Relation alldata;
	map<string, Scheme> storem;
	vector<string> tuscheme;

	dave = dats;

	string nams;
	//int i = 1;

	for (unsigned int i = 0; i < dats.getSchemes().size(); i++) {
		//tootoo.push_back(dats.getschemes()[i].getval());
		//Scheme tootoo;
		vector<string> pushable;
		nams = dats.getSchemes()[i].getVal();
		i++;
		while (dats.getSchemes()[i].getVal() != ")") {
			if (dats.getSchemes()[i].getType() == ID) {
				pushable.push_back(dats.getSchemes()[i].getVal());

			}
			i++;
		}

		alldata = Relation(pushable);
		everything[nams] = alldata;

	}

	Toople tryit;
	vector<Token> demFacts = dats.getFacts();

	for (unsigned int i = 0; i <dats.getFacts().size(); i++) {

		nams = dats.getFacts()[i].getVal();
		Toople tufact;

		while (demFacts[i].getVal() != ".") {

			if (demFacts[i].getType() == STRING) {

				tufact.push_back(demFacts[i].getVal());
				tryit = tufact;
			}

			i++;
		}

		everything.at(nams).addTuple(tufact);


	}

	evalQueries();

	//ask about workaround for not allowing duplicates

}

string Interpreter::evalQueries() {
	string returnable;
	for (unsigned int i = 0; i < dave.getQueries().size(); i++) {

		Relation evaled = eval1Quer(dave.getQueries()[i]);



	}
	return returnable;
}

//could change function to return a string instead.
Relation Interpreter::eval1Quer(Predicate quer) {
	string table;
	table = quer.getID().getVal();
	parameter checkSeen;
	map<string, int> reviewed;
	vector<string> toProject;
	vector<int> toRename;
	//vector<parameter> keep;

	vector<parameter> paras = quer.getParams();
	Relation lookat = everything.at(table);
	Relation returnable;
	for (unsigned int i = 0; i < paras.size(); i++) {
		//constants
		if (paras[i].getConst() == true) {
			lookat = lookat.select(paras[i].toString(), i);

		}
		else {

			if (reviewed.count(paras[i].toString()) >= 1) {
				//Don't really get type 2 select and how to implement
				lookat = lookat.select(paras[i].toString(), reviewed.at(paras[i].toString()), i);
			}
			else {
				//variables
				keep.push_back(paras[i]);
				stores[paras[i].toString()] = i;
				reviewed[paras[i].toString()] = i;
				toProject.push_back(paras[i].toString());
				toRename.push_back(i);
				//Relation temp = returnable;
				//checkSeen = paras[i];
			}
		}
	}

	returnable = lookat;


	for (unsigned int i = 0; i < toProject.size(); i++) {
		//may need to rewrite this to make it faster in later labs

		//returnable = rename(returnable, toProject[i], toRename[i]);
		returnable = returnable.rename(toProject[i], toRename[i]);
	}


	/*
	for (int i = 0; i < returnable.getName().size(); i++) {
		cout << returnable.getName()[i];
	}*/
	returnable = returnable.project(toProject);

	totalQuer += quer.toString() + "?";
	if (returnable.getTup().size() > 0) {
		//There is an issue here. Not sure why getTup doesn't really want to work.
		totalQuer += " Yes(";
		totalQuer += to_string(returnable.getTup().size());
		totalQuer += ")\n";
		for (Toople T : returnable.getTup()) {
			//int q = T.size();
			for (unsigned int i = 0; i < T.size(); i++) {
				totalQuer += "  " + returnable.getName()[i];
				totalQuer += "=" + T[i] + ",";
			}
			totalQuer.pop_back();
			totalQuer += "\n";
		}
		totalQuer.pop_back();



	}
	else {
		totalQuer += " No";
	}
	totalQuer += "\n";


	return returnable;
}

/*
Relation Interpreter:: select(Relation datas, string getem, int col) {

	//I think that the best way for me to fix this will be to overload the function,
	//and have another select function that can take in a vector of integers

	vector<string> column;
	column.push_back(datas.getName()[col]);

	Relation returnable = Relation(datas.getName());

	set <Toople> searchem = datas.getTup();

	for (set<Toople>::iterator it = searchem.begin(); it != searchem.end(); ++it) {
		vector <string> looks = *it;
		if (looks[col] == getem) {
			returnable.addTuple(*it);
		}
	}
	return returnable;
}

Relation Interpreter:: rename(Relation toChange, string changeTo, int col) {
	Relation returnable;
	vector<string> newName;
	newName = toChange.getName();


	replace(newName.begin(), newName.end(), toChange.getName()[col], changeTo);
	returnable = Relation(newName);
	vector<Toople> transfer;
	set<Toople> toVector = toChange.getTup();

	for (set<Toople>::iterator it = toVector.begin(); it != toVector.end(); ++it) {
		returnable.addTuple(*it);
	}

	return returnable;
}

Relation Interpreter:: project(Relation toChange, vector<string> toProject) {
	Relation returnable;
	returnable = Relation(toProject);
	set<Toople> transfer = toChange.getTup();
	int counter = 0;
	//getting the column numbers
	vector<int> colNum;
	for (int j = 0; j < toProject.size(); j++) {
		for (int i = 0; i < toChange.getName().size(); i++) {
			if (toProject[j] == toChange.getName()[i]) {
				colNum.push_back(i);
			}
		}
	}


	for (Toople toop : toChange.getTup()) {
		Toople toPush;
		for (int i = 0; i < colNum.size(); i++) {
			toPush.push_back(toop[colNum[i]]);
		}
		returnable.addTuple(toPush);
	}


			return returnable;
}
*/

string Interpreter::toString() {
	string returnable;

	returnable += totalQuer;
	/*
	for (pair <string, Relation> p : everything) {
		returnable += p.first;
		returnable += "\n";
		returnable += p.second.toString();
	}
	returnable += "\n";
	*/
	return returnable;
}



/*
TODO:
make rename take in all the things to rename
put the select, rename, and project functions into the relation class
Need to fix all those because I only get up to 1 value for everything, and they don't print
*/
