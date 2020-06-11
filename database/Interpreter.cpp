

#include "Interpreter.h"
#include <list>
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
	//will have to figure out what to do with trivial cases (only run rule once on those)

	depGraph(dats.getRules());
	vector<vector<int>> totSCC;
	//int weOn = 0;
	totSCC = SCC();

	for (unsigned int i = 0; i < totSCC.size(); i++) {
		vector<int> ruleNumber;
		passes = 0;
		bool time1 = true;
		if (totSCC[i].size() == 1) {
			for (int k : graph[totSCC[i][0]].edges) {
				if (k == totSCC[i][0]) {
					time1 = false;
				}
			}
			if (time1) {
				//what in typical situation 
				allRules += "\nSCC: R" + to_string(totSCC[i][0]);
				allRules += "\n" + graph[totSCC[i][0]].rul.toString();
				eval1Rule(graph[totSCC[i][0]].rul);
				allRules += "\n1 passes: R" + to_string(totSCC[i][0]);
				continue;
			}
		}
		vector<Rule> red4eval;
		for (unsigned int j = 0; j < totSCC[i].size(); j++) {
			ruleNumber.push_back(totSCC[i][j]);
			red4eval.push_back(graph[totSCC[i][j]].rul);
			//cout << graph[totSCC[i][j]].rul.toString();
		}
		allRules += "\nSCC: ";
		for (unsigned int j = 0; j < ruleNumber.size(); j++) {
			// we haz sum problems here
			allRules += "R";
			//string nnknkn = to_string(ruleNumber[i]);
			allRules += to_string(ruleNumber[j]);
			allRules += ",";
		}
		if (ruleNumber.size() >= 1) {
			allRules.pop_back();
		}
		//allRules += "\nSCC: R" + to_string(ruleNumber[weOn]);
		evalRules(red4eval);
		passes++;
		while (tupAdded) {
			evalRules(red4eval);
			passes++;
		}
		allRules += "\n" + to_string(passes);
		allRules += " passes: ";
		for (unsigned int j = 0; j < ruleNumber.size(); j++) {
			allRules += "R" + to_string(ruleNumber[j]) + ",";
		}
		allRules.pop_back();
		//weOn++;

	}

	



	evalQueries();


	/*
	int ruleHead = 0;
	for (pair<string, Relation> relString : Ruled) {
		allRules += dats.getRules()[ruleHead].toString();
		if(relString.second.getTup().size() > 0){
			allRules += relString.second.toString();
		}
		allRules += "\n";
		ruleHead++;
	}
	*/

}

void Interpreter:: depGraph(vector<Rule> ruleList) {
	for (unsigned int i = 0; i < ruleList.size(); i++) {
		Node temp = Node(i, ruleList[i]);
		
		graph[i] = temp;
		reverseGraph[i] = temp;
	}


	for (unsigned int i = 0; i < ruleList.size(); i++) {
		for (unsigned int g = 0; g < ruleList[i].getRules().size(); g++) {
			for (unsigned int k = 0; k < ruleList.size(); k++) {
				if (ruleList[i].getRules()[g].getID().getVal() == ruleList[k].getHead().getID().getVal()) {
					graph.at(i).edges.insert(k);
				}
			}
		}
	}
	reverseDepGraph(graph);
}

void Interpreter:: reverseDepGraph(map<int, Node> firstGraph) {
	
	int k = 0;
	for (pair<int, Node> element : firstGraph) {
		for (int i : element.second.edges) {
			//set<int> addin = reverseGraph.at(i).edges;
			reverseGraph.at(i).edges.insert(element.first);
			//addin.insert(k);
		}
		k++;
	}


	//returnable += "\n";

	postNum = 1;
	for (pair<int, Node> element : reverseGraph) {
		if (element.second.visited == false) {
			DFSForest(element.first);
		}
	}



}
//recommended that this be in a graph class. 
int Interpreter:: DFSForest(int rulNum) {
	//ask about this one. Looks like an infinite loop to me. 
	//may need to look through the edges to see which one is the lowest number and then check if it was visted starting w/lowest
	reverseGraph.at(rulNum).visited = true;
	for (int i : reverseGraph.at(rulNum).edges) {
		if (reverseGraph.at(i).visited == false) {
			//reverseGraph.at(rulNum).visited = true;
			DFSForest(i);
		}
	}
	//reverseGraph.at(rulNum).visited = true;
		reverseGraph.at(rulNum).postorder = postNum;
		allPosts.push(rulNum);
		worthlessToo.push_back(rulNum);
		//reverseGraph.at(rulNum).visited = true;
		postNum++;
	return rulNum;
}
vector<vector<int>> Interpreter:: SCC() {
	vector<vector<int>> returnable;
	//int start;
	//int bigPost = 1;
	/*
	for (pair<int, Node> element : graph) {
		element.second.visited = false;
		
		if (element.second.postorder > bigPost) {
			bigPost = element.second.postorder;
			start = element.first;
		}
	
	}
	*/


	worthless = allPosts.top();
	while (!allPosts.empty()) {
		//cout << "\nwhere we at: " << allPosts.top() << endl;
		SCCGroup.clear();
		worthless = 0;
		DFSForward(allPosts.top());
		sort(SCCGroup.begin(), SCCGroup.end());
		returnable.push_back(SCCGroup);
		//cout << SCCGroup.size();
	}

	
	
	return returnable;
}

int Interpreter::DFSForward(int rulNum) {

	//cout << "WHY?!?!?\n" << rulNum << graph.at(rulNum).edges.size() << graph.at(rulNum).rul.toString();
	graph.at(rulNum).visited = true;
		
	for (int i : graph.at(rulNum).edges) {
		if (graph.at(i).visited == false) {
			//cout << graph.at(rulNum).edges.size();
			DFSForward(i);
		}
	}
	graph.at(rulNum).visited = true;
		worthless++;
		allPosts.pop();
		SCCGroup.push_back(rulNum);
		//SCCGroup.push_back(rulNum);
	return rulNum;
}

void Interpreter::evalRules(vector<Rule> evaluatate) {

	tupAdded = false;
	for (unsigned int i = 0; i < evaluatate.size(); i++) {
			allRules += "\n" + evaluatate[i].toString();
		Ruled[evaluatate[i].getHead().getID().getVal()] = Relation(eval1Rule(evaluatate[i]));
	}

	//ask someone how they would recommend checking for a change in the tuples from this

}

Relation Interpreter::eval1Rule(Rule toEval) {
	//could try changing the rename functions to see if that helps
	Predicate header = toEval.getHead();
	string table = header.getID().getVal();
	//creating new relations from evaluating the rule
	vector<string> scheme;

	for (unsigned int i = 0; i < header.getIDs().size(); i++) {


		scheme.push_back(header.getIDs()[i].getVal());

	}

	Relation returnable = Relation(scheme);

	vector<Relation> evaled;
	vector<Predicate> pred4eval = toEval.getRules();
	for (unsigned int i = 0; i < pred4eval.size(); i++) {
		evaled.push_back(evalPredicate(pred4eval[i]));
	}
	//set <Toople> lookin = evaled[0].getTup();





	vector<Relation> temp = evaled;
	vector<Relation> afterJoin;
	while(evaled.size() >= 2){
		evaled[0] = evaled[0].join(evaled[1]);
		evaled.erase(evaled.begin()+1);

	}





	vector <int> colNums;
	string printer;
	for (unsigned int i = 0; i < everything[table].getName().size(); i++) {

		printer += (everything[table].getName().at(i));
		colNums.push_back(i);
	}

	Relation toRename = evaled[0];

	

	Relation Renamed = toRename.project(scheme);
	//will need to rename here. Need to rename to value of everything[table].getName();


	for (unsigned int i = 0; i < everything[table].getName().size(); i++) {
		Renamed = Renamed.rename(everything[table].getName()[i], colNums[i]);
	}

	unsigned int check = everything[table].getTup().size();

	//returnable = united(everything[table], Renamed);

	vector<string> addon;
	addon = everything[table].Uniter(Renamed);

	



	//getting the string for all rules
	

	/*
	if (everything[table].getTup().size() < returnable.getTup().size()) {
		int onlyNew = everything[table].getTup().size();
		int counter = 1;
		for (Toople tup : returnable.getTup()) {
			if (counter > onlyNew) {
				vector<string> adder = tup;
				allRules += "   ";
				for (unsigned int i = 0; i < tup.size(); i++) {
					allRules += "  " + returnable.getName()[i];
					allRules += "=" + tup[i] + ",";
				}
				allRules.pop_back();
			}
			counter++;
		}
	}
	*/

	for (unsigned int i = 0; i < addon.size(); i++) {
		allRules += addon[i];
	}

	//everything[table] = returnable;

	if (everything[table].getTup().size() > check) {
		tupAdded = true;
	}

	return returnable;
}


Relation Interpreter::evalPredicate(Predicate toEval) {
	string table;
	table = toEval.getID().getVal();
	parameter checkSeen;
	map<string, int> reviewed;
	vector<string> toProject;
	vector<int> toRename;
	//vector<parameter> keep;
	//cout << endl << table << " eval preds " << toEval.getParams().size() << endl;

	if (everything.count(table) < 1) {
		//hopefully will fix some bugs.
		toProject.push_back(table);
		Relation returnable = Relation(toProject);
		return returnable;
	}
	vector<parameter> paras = toEval.getParams();
	Relation lookat = everything.at(table);
	Relation returnable;
	for (unsigned int i = 0; i < paras.size(); i++) {
		//constants
		if (paras[i].getConst() == true) {
			//cout << "shouldn't be hittin this";
			lookat = lookat.select(paras[i].toString(), i);

		}
		else {

			if (reviewed.count(paras[i].toString()) >= 1) {
				//cout << "why we hittin this?";
				//Don't really get type 2 select and how to implement
				lookat = lookat.select(paras[i].toString(), reviewed.at(paras[i].toString()), i);
			}
			else {
				//variables
				//cout << "is we hittin here?";
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
	//cout << returnable.getTup().size() << endl;
	if (returnable.getTup().size() > 1) {
		//cout << "she aint empty, why ";
	}
		//could check here to see what tups the relation has.


		//may need to rewrite this to make it faster in later labs

		//returnable = rename(returnable, toProject[i], toRename[i]);
		for (unsigned int i = 0; i < toProject.size(); i++) {
			returnable = returnable.rename(toProject[i],toRename[i]);
		}
		//returnable = returnable.rename(toProject, toRename);

		returnable = returnable.project(toProject);


		/*
		for (int i = 0; i < returnable.getName().size(); i++) {
			cout << returnable.getName()[i] << " ";
			cout << toProject[i] << " ";
		}
		*/

	/*
	for (int i = 0; i < returnable.getName().size(); i++) {
		cout << returnable.getName()[i];
	}*/
	//returnable = returnable.project(toProject); //issue here
	/*
	vector<string> varName;
	for (Toople why : returnable.getTup()) {
		for (int i = 0; i < why.size(); i++) {
			varName.push_back(why[i]);
		}
	}
	for (int i = 0; i < varName.size(); i++) {
		cout << varName[i] << " ";
	}
	*/

	vector<string> toPrint;
	for (Toople why : returnable.getTup()) {
		for (unsigned int i = 0; i < why.size(); i++) {
			toPrint.push_back(why[i]);
		}
	}
	for (unsigned int i = 0; i < toPrint.size(); i++) {
		//cout << endl << "did we not go here?";
		//cout << toPrint[i] << " ";
	}

	return returnable;
}

Relation Interpreter:: united(Relation old, Relation toAdd) {
	Relation returnable = old;
	for (Toople tup : toAdd.getTup()) {
		returnable.addTuple(tup);
	}
	return returnable;
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

	returnable += "Dependency Graph\n";
	for (pair<int, Node> element : graph) {
		returnable += "R" + to_string(element.first) + ":";
		for (int j : element.second.edges) {
			returnable += "R" + to_string(j) + ",";
		}
		if (element.second.edges.size() >= 1) {
			returnable.pop_back();
		}
		returnable += "\n";
	}
	returnable += "\n";


	returnable += allRules;

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
