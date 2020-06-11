#include "Rule.h"

Rule::Rule() {

}
Rule::Rule(Predicate head, Token col, vector<Predicate> rulz, Token per) {
	header = head;
	colDash = col;
	rules = rulz;
	period = per;
}

string Rule::toString() {
	string returnable;
	returnable += header.toString();
	returnable += " ";
	returnable += colDash.getVal();
	returnable += " ";
	for (unsigned int i = 0; i < rules.size(); i++) {
		returnable += rules[i].toString();
		returnable += ",";
	}
	returnable.pop_back();
	returnable += period.getVal();
	return returnable;
}


/*
string Rule::toString() {
	string returnable;
	for (int i = 0; i < rules.size(); i++) {
		returnable += rules[i].toString();
		//may need to add endl
	}
	return returnable;
}
*/
