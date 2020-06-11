

#include "datalog.h"


datalog::datalog(){

}

datalog::datalog(vector<Token> schem, vector<Token> fac, vector<Rule> rul, vector<Predicate> quer) {
	schemes = schem;
	facts = fac;
	queries = quer;
	rules = rul;

	for (unsigned int i = 0; i < facts.size(); i++) {
		if (facts[i].getType() == STRING) {
			//Token thingy = facts[i];
			domains.insert(facts[i].getVal());
		}
		else{}
	}



}

string datalog::toString() {
	string returnable;
	//int temp;
	unsigned int i = 0;
	int size = 0;

	while (schemes.size() > i) {
		if (schemes[i].getType() == RIGHT_PAREN) {
			size++;
		}
		/*
		cout << schemes[i].getVal() << " ";
		*/
		i++;
	}

	returnable += "Schemes(";
	returnable += to_string(size);
	returnable += "):\n  ";
	for (unsigned int i = 0; i < schemes.size(); i++) {
		returnable += schemes[i].getVal();
		if (schemes[i].getType() == RIGHT_PAREN) {
			returnable += "\n  ";
		}
	}
	for (int g = 0; g < 2; g++) {
		returnable.pop_back();
	}

	size = 0;
	i = 0;

	while (facts.size() > i) {
		if (facts[i].getType() == PERIOD) {
			size++;
		}
		i++;
	}
	returnable += "Facts(";
	returnable += to_string(size);
	returnable += "):\n  ";
	for (unsigned int i = 0; i < facts.size(); i++) {
		returnable += facts[i].getVal();
		if (facts[i].getType() == PERIOD) {
			returnable += "\n  ";
		}
	}
	for (int g = 0; g < 2; g++) {
		returnable.pop_back();
	}
/*
	returnable += "Test rules ";
	for (unsigned int i = 0; i < rules.size(); i++) {
		returnable += rules[i].toString();
		returnable += "\n";
	}
*/
	returnable += "Rules(";
	returnable += to_string(rules.size());
	returnable += "):\n  ";
	for (unsigned int i = 0; i < rules.size(); i++) {
		returnable += rules[i].toString();
		returnable += "\n  ";
	}
	for (int g = 0; g < 2; g++) {
		returnable.pop_back();
	}

	returnable += "Queries(";
	returnable += to_string(queries.size());
	returnable += "):\n  ";
	for (unsigned int i = 0; i < queries.size(); i++) {
		returnable += queries[i].toString();
		returnable += "?\n  ";
	}
	for (int g = 0; g < 3; g++) {
		returnable.pop_back();
	}
	//returnable += "?";
	returnable += "\n";

	returnable += "Domain(";
	returnable += to_string(domains.size());
	returnable += "):\n  ";
	//Token z;

	for (auto z = domains.begin(); z != domains.end(); ++z) {
		returnable += *z;
		returnable += "\n  ";
	}
	for (int g = 0; g < 2; g++) {
		returnable.pop_back();
	}

	return returnable;
}


vector<Token> datalog::getSchemes() {
	return schemes;
}


vector<Token> datalog::getFacts() {
	return facts;
}


vector<Rule> datalog::getRules() {
	return rules;
}


vector<Predicate> datalog::getQueries() {

	return queries;
}