
#include "Predicate.h"

Predicate::Predicate() {

}

Predicate::Predicate(Token id, Token lPar, vector<parameter> paraList, Token rPar) {
	iD = id;
	leftPar = lPar;
	params = paraList;
	rightPar = rPar;
	head = false;
}

Predicate::Predicate(Token id, Token lPar, vector<Token> paraList, Token rPar) {
	iD = id;
	leftPar = lPar;
	ids = paraList;
	rightPar = rPar;
	head = true;
}

Token Predicate::getID() {
	return iD;
}

vector<parameter>Predicate:: getParams() {
	return params;
}

vector<Token>Predicate::getIDs() {
	vector<Token> temp;
	for (unsigned int i = 0; i < ids.size(); i++) {
		if (ids[i].getType() == ID) {
			temp.push_back(ids[i]);
		}
	}
	return temp;
}

string Predicate::toString() {
	string returnable;
	if (head == false) {
		returnable += iD.getVal();
		returnable += leftPar.getVal();
		for (unsigned int i = 0; i < params.size(); i++) {
			returnable += params[i].toString();
			returnable += ",";
		}
		returnable.pop_back();
		returnable += rightPar.getVal();
	}
	else if(head == true) {
		returnable += iD.getVal();
		returnable += leftPar.getVal();
		for (unsigned int i = 0; i < ids.size(); i++) {
			returnable += ids[i].getVal();
		}
		returnable += rightPar.getVal();
	}
	//returnable += rightPar.getVal();
	return returnable;
}
