
#include "parser.h"


parser::parser(vector<Token> toParse) {
	scanned = toParse;
	try {
		total = datalogParse(scanned[location]);
	}
	catch(Token bad){
		cout << "Failure!" << endl;
		cout << "  " << bad.toString() << ")\n";
		success = false;
	}

	//cout << "Success!" << endl;
	//cout toString()
}

//

datalog parser::datalogParse(Token currentToken) {
	vector<Token> schemeMe;
	vector<Token> tempScheme;
	vector<Token> factMe;
	vector<Token> tempFact;
	vector<Rule> ruleMe;
	vector<Rule> tempRule;
	vector<Predicate> querieMe;
	vector<Predicate> tempQuerie;

	match(SCHEMES);
	//location++;
	match(COLON);
	//location++;
	tempScheme = scheme(scanned[location]);
	schemeMe.insert(schemeMe.end(), tempScheme.begin(), tempScheme.end());
	tempScheme = schemeList(scanned[location]);
	schemeMe.insert(schemeMe.end(), tempScheme.begin(), tempScheme.end());
	if (schemeMe.size() == 2) {
		//cout << "nun scheme";
		throw scanned[location];
	}
	match(FACTS);
	//location++;
	match(COLON);
	tempFact = factList(scanned[location]);
	factMe.insert(factMe.end(), tempFact.begin(), tempFact.end());

	match(RULES);
	match(COLON);
	tempRule = ruleList(scanned[location]);
	ruleMe.insert(ruleMe.end(), tempRule.begin(), tempRule.end());

	match(QUERIES);
	match(COLON);
	querieMe.push_back(query(scanned[location]));
	tempQuerie = queryList(scanned[location]);
	querieMe.insert(querieMe.end(), tempQuerie.begin(), tempQuerie.end());
	if (querieMe.size() < 1) {
		//cout << "nun quer";
		throw scanned[location];
	}
	if(scanned[location].getType() != endOF){
		throw scanned[location];
	}
	return datalog(schemeMe,factMe,ruleMe,querieMe);
}

vector<Token> parser::schemeList(Token currentToken) {
	vector<Token> returnable;
	vector<Token> temp1;
	vector<Token> temp2;
	if (currentToken.getType() == ID) {
		temp1 = scheme(scanned[location]);
		temp2 = schemeList(scanned[location]);
		returnable.insert(returnable.end(), temp1.begin(), temp1.end());
		returnable.insert(returnable.end(), temp2.begin(), temp2.end());
		return returnable;
	}
	else {/*lambda*/ }
	return returnable;
}

vector<Token> parser::factList(Token currentToken) {
	vector<Token> returnable;
	vector<Token> temp1;
	vector<Token> temp2;
	if (currentToken.getType() == ID) {
		temp1 = fact(scanned[location]);
		temp2 = factList(scanned[location]);
		returnable.insert(returnable.end(), temp1.begin(), temp1.end());
		returnable.insert(returnable.end(), temp2.begin(), temp2.end());
		return returnable;
	}
	else {
		/*lambda*/
	}
	return returnable;
}

vector<Rule> parser::ruleList(Token currentToken) {
	vector<Rule> returnable;
	vector<Rule> temp1;
	vector<Rule> temp2;
	if (currentToken.getType() == ID) {
		returnable.push_back(rule(scanned[location]));
		temp2 = ruleList(scanned[location]);
		returnable.insert(returnable.end(), temp2.begin(), temp2.end());
		return returnable;
	}
	else{/*lambda*/ }
	return returnable;
}

vector<Predicate> parser::queryList(Token currentToken) {
	vector<Predicate> returnable;
	vector<Predicate> temp;
	if (currentToken.getType() == ID) {
		returnable.push_back(query(scanned[location]));
		temp = queryList(scanned[location]);
		returnable.insert(returnable.end(), temp.begin(), temp.end());
		return returnable;
	}
	else {/*lambda*/ }
	return returnable;
}

vector<Token> parser:: scheme(Token currentToken) {
	vector<Token> returnable;
	vector<Token> temp;
	match(ID);
	returnable.push_back(scanned[location-1]);
	match(LEFT_PAREN);
	returnable.push_back(scanned[location-1]);
	match(ID);
	returnable.push_back(scanned[location-1]);
	temp = idList(scanned[location]);
	returnable.insert(returnable.end(), temp.begin(), temp.end());
	match(RIGHT_PAREN);
	returnable.push_back(scanned[location-1]);

	return returnable;
}

vector<Token> parser::fact(Token currentToken) {
	vector<Token> returnable;
	vector<Token> temp;
	match(ID);
	returnable.push_back(scanned[location - 1]);
	match(LEFT_PAREN);
	returnable.push_back(scanned[location - 1]);
	match(STRING);
	returnable.push_back(scanned[location - 1]);
	//domain.insert(scanned[(location - 1)].getVal());
	temp = stringList(scanned[location]);
	returnable.insert(returnable.end(), temp.begin(), temp.end());
	match(RIGHT_PAREN);
	returnable.push_back(scanned[location - 1]);
	match(PERIOD);
	returnable.push_back(scanned[location - 1]);
	return returnable;
}

Rule parser::rule(Token currentToken) {
	Predicate head;
	vector<Predicate> predList;
	vector<Predicate> temp;
	Token colDash;
	Token per;
	head = headPredicate(scanned[location]);
	match(COLON_DASH);
	colDash = scanned[location - 1];
	predList.push_back(predicate(scanned[location]));
	temp = predicateList(scanned[location]);
	predList.insert(predList.end(),temp.begin(), temp.end());
	match(PERIOD);
	per = scanned[location - 1];
	//probably have to add to rules vector here
	return Rule(head,colDash,predList,per);
}

Predicate parser::query(Token currentToken) {
	Predicate returnable;
	returnable = predicate(scanned[location]);
	match(Q_MARK);
	return returnable;
}


Predicate parser::headPredicate(Token currentToken) {
	Token id;
	Token leftPar;
	vector<Token> allIds;
	vector<Token> temp;
	Token rightPar;
	match(ID);
	id = scanned[location - 1];
	match(LEFT_PAREN);
	leftPar = scanned[location - 1];
	match(ID);
	allIds.push_back(scanned[location - 1]);
	temp = idList(scanned[location]);
	allIds.insert(allIds.end(), temp.begin(), temp.end());
	match(RIGHT_PAREN);
	rightPar = scanned[location - 1];
	return Predicate(id,leftPar,allIds,rightPar);

}

Predicate parser::predicate(Token currentToken) {
	Token id;
	Token leftPar;
	vector<parameter> params;
	Token rightPar;
	vector<parameter> temp;
	unsigned int j = 0;
	match(ID);
	id = scanned[location - 1];
	match(LEFT_PAREN);
	leftPar = scanned[location - 1];
	params.push_back(Parameter(scanned[location]));
	temp = (parameterList(scanned[location]));
	while (temp.size() > j) {
		parameter par = temp[j];
		params.push_back(par);
		j++;
	}
	temp.clear();
	match(RIGHT_PAREN);
	rightPar = scanned[location - 1];
	return Predicate(id,leftPar,params,rightPar);

}

vector<Predicate> parser::predicateList(Token currentToken) {
	//Token com;
	vector<Predicate> returnable;
	vector<Predicate> temp;
	while(scanned[location].getType() == COMMA){
		match(COMMA);
		returnable.push_back(predicate(scanned[location]));
		//returnable.push_back(predicate(scanned[location]));
		//temp = predicateList(scanned[location]);
		//returnable.insert(returnable.end(), temp.begin(), temp.end());
	}
	/*
	if (currentToken.getType() == COMMA) {
		match(COMMA);
		returnable.push_back(predicate(scanned[location]));
		temp = predicateList(scanned[location]);
		returnable.insert(returnable.end(), temp.begin(), temp.end());
		return returnable;
	}
	else {}
	*/
	return returnable;
}


vector<parameter> parser::parameterList(Token currentToken) {
	vector<parameter> returnable;

	while(scanned[location].getType() == COMMA){
		match(COMMA);
		returnable.push_back(Parameter(scanned[location]));
		//location++;
	}
	/*
	if (currentToken.getType() == COMMA) {
		match(COMMA);
		//not sure how to deal with the comma here
		//returnable.push_back(scanned[location - 1].getVal());
		returnable.push_back(Parameter(scanned[location]));
		parameterList(scanned[location]);
		return returnable;
	}
	else {}
	*/
	return returnable;
}

vector<Token> parser::stringList(Token currentToken) {
	//vector<Token> returnable = stringVec;
	vector<Token> returnable;
	while (scanned[location].getType() == COMMA) {
		match(COMMA);
		returnable.push_back(scanned[location - 1]);
		match(STRING);
		returnable.push_back(scanned[location - 1]);
	}

	/*
	if (currentToken.getType() == COMMA) {
		match(COMMA);
		stringVec.push_back(scanned[location - 1]);
		match(STRING);
		stringVec.push_back(scanned[location - 1]);
		stringList(scanned[location]);
		return returnable;
	}
	else {}
	*/
	return returnable;


}


vector<Token> parser::idList(Token currentToken) {
	vector<Token> returnable;
	while (scanned[location].getType() == COMMA) {
		match(COMMA);
		returnable.push_back(scanned[location - 1]);
		match(ID);
		returnable.push_back(scanned[location - 1]);
		//return returnable;
	}
	/*
	if (currentToken.getType() == COMMA) {
		match(COMMA);
		idVec.push_back(scanned[location - 1]);
		match(ID);
		idVec.push_back(scanned[location - 1]);
		idList(scanned[location]);
		return returnable;
	}
	*/
	//else{/*lambda*/ }
	return returnable;


}

parameter parser::Parameter(Token currentToken) {
	//string param = "";
	parameter returnable;
	tokenType tok = scanned[location].getType();
	if (tok == STRING) {
		match(STRING);
		//param += scanned[location - 1].getVal();
		returnable = parameter(scanned[location-1]);
		return returnable;
	}
	if (tok == ID) {
		match(ID);
		//param += scanned[location - 1].getVal();
		returnable =  parameter(scanned[location - 1]);
		return returnable;
	}
	if (tok == LEFT_PAREN) {
		//param += expression(currentToken);
		returnable =  parameter(express(currentToken));
		return returnable;
	}
	else {
		//cout << "error here" << endl;
		bad = scanned[location];
		throw scanned[location];
		//error(scanned[location]);
		return returnable;
	}
	return returnable;
}

string parser::express(Token currentToken) {
	//string returnable = "";
	string returnable;
	Token leftParen;
	parameter leftParam;
	Token op;
	parameter rightParam;
	Token rightParen;
	match(LEFT_PAREN);
	returnable += scanned[location - 1].getVal();
	leftParam = Parameter(scanned[location]);
	returnable += leftParam.toString();
	returnable += Operator(scanned[location]).getVal();
	//returnable += currentToken.getVal();
	rightParam = Parameter(scanned[location]);
	returnable += rightParam.toString();
	match(RIGHT_PAREN);
	returnable += scanned[location - 1].getVal();

	//returnable = expression(leftParen, leftParam, op, rightParam, rightParen);
	return returnable;
}

Token parser::Operator(Token currentToken) {
	Token returnable;
	tokenType tok = scanned[location].getType();
	if (tok == ADD) {
		match(ADD);
		returnable =  scanned[location - 1];
		return returnable;
	}
	if (tok == MULTIPLY) {
		match(MULTIPLY);
		returnable =  scanned[location - 1];
		return returnable;
	}
	else {
		//error(scanned[location]);
		//cout << "error operator" << endl;
		bad = scanned[location];
		throw scanned[location];
		return returnable;
	}
	return returnable;

}


Token parser::match(tokenType currentToken) {
	Token returnable = scanned[location];
	Token compare = scanned[location];
	if (compare.getType() == currentToken) {

	}
	else {
		//tried figuring out why I was getting an error.
		//cout << "error match "  << location << " " << scanned[location].getType() << " " << currentToken << endl;
		bad = scanned[location];
		throw scanned[location];
		//error(scanned[location]);
	}
	location++;
	return returnable;
}

datalog parser::getTotal() {
	return total;
}

/*
void parser::error(Token token) {
	try {
		throw token.getType();
	}
	catch(token.getType()){
		cout << "failure!" << endl;
		cout << token.toString();
	}
}
*/



/*
Problems I have right now that I need to figure out:
What to check for when looking at functions w/lambda
where to implement match
how to implement error() w/try/catch

*/
