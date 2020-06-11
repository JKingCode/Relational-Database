

#include "scanner.h"
#include "Token.h"
using namespace std;

scanner::scanner(string fileName) {
	in.open(fileName);
	currentChar = ' ';

}

char scanner :: Scan() {
	while (in.peek() != EOF) {
		currentChar = in.get();
		if (isspace(currentChar)) {
			//skip
			if (currentChar == '\n') {
				lineNumber++;
			}
			continue;
		}

			switch (currentChar) {
			case ',': tokVec.push_back(Token(COMMA, ",", lineNumber)); break;
			case '.': tokVec.push_back(Token(PERIOD, ".", lineNumber)); break;
			case '?': tokVec.push_back(Token(Q_MARK, "?", lineNumber)); break;
			case '(': tokVec.push_back(Token(LEFT_PAREN, "(", lineNumber)); break;
			case ')': tokVec.push_back(Token(RIGHT_PAREN, ")", lineNumber)); break;
			case '*': tokVec.push_back(Token(MULTIPLY, "*", lineNumber)); break;
			case '+': tokVec.push_back(Token(ADD, "+", lineNumber)); break;
			case '\'':
				/*strings
				if (in.peek() == '\'') {
					//int trackLine = 0;
					string apostrophe;
					apostrophe += currentChar;
					while (in.peek() == '\'') {
						apostrophe += in.get();
					}
					if (in.peek() == '\n') {
						lineNumber++;
					}
					in.get();
					cout << apostrophe << endl;
					tokVec.push_back(Token(STRING, apostrophe, lineNumber));
					break;
				}
				*/
				fullString += currentChar;
				stringer(in.get());
				break;
				//getaString(); break;
			case '#': if (in.peek() == '|') {
				//block comment
				getBlockComment();
			}
					else {
				//line comment
				string theComments = "#";
				while (in.peek() != '\n') {
					theComments += in.get();
				}
				tokVec.push_back(Token(COMMENT, theComments, lineNumber));
			}break;
			case ':': if (in.peek() == '-') {
				//colonDash
				in.get();
				tokVec.push_back(Token(COLON_DASH, ":-", lineNumber));
				break;
			}
					else {
				tokVec.push_back(Token(COLON, ":", lineNumber));
				break;
			}
					break;
			default:

				//will have to do string check here
				if (isalpha(currentChar)) {
					scanId(currentChar);
					break;
				}
				else {
					//undefined character
					string character = "";
					character.push_back(currentChar);
					tokVec.push_back(Token(UNDEFINED, character, lineNumber));
					break;
				}
				break;


			}
		}
		//eof
	tokVec.push_back(Token(endOF, "", lineNumber));
	return currentChar;
	}



string scanner :: scanId(char curr) {
	string IDed;
	IDed += curr;
	char curcar;
	char see;
	while ((isalnum(see = in.peek()))) {
		curcar = in.get();
		IDed += curcar;
	}
	if (IDed == "Schemes") {
		//SCHEMES
		tokVec.push_back(Token(SCHEMES, "Schemes", lineNumber));
	}
	else if (IDed == "Facts") {
		//FACTS
		tokVec.push_back(Token(FACTS, "Facts", lineNumber));
	}
	else if (IDed == "Rules") {
		//RULES
		tokVec.push_back(Token(RULES, "Rules", lineNumber));
	}
	else if (IDed == "Queries") {
		//QUERIES
		tokVec.push_back(Token(QUERIES, "Queries", lineNumber));
	}
	else {
		//ID
		string stringOfID;
		//stringOfID = "\"" + IDed + "\"";
		stringOfID = IDed;
		tokVec.push_back(Token(ID, stringOfID, lineNumber));
	}
	return IDed;
}
//trying out a recursive get a string function

bool scanner::stringer(char current) {
	char hereWeAre = current;

	if(hereWeAre == '\n'){
	keepNumber ++;
	}
	if (hereWeAre == '\''){
		/*while (in.peek() == '\'') {
			fullString += hereWeAre;
			in.get();
		}*/
		if(in.peek() == '\''){
			fullString += hereWeAre;
			fullString += in.get();
			stringer(in.get());
			return true;
		}
		else{
		fullString += hereWeAre;
		tokVec.push_back(Token(STRING, fullString, lineNumber));
		fullString = "";
		lineNumber += keepNumber;
		keepNumber = 0;
		return true;
		}
	}
	else if (in.peek() == EOF) {
		fullString += hereWeAre;
		tokVec.push_back(Token(UNDEFINED, fullString, lineNumber));
		fullString = "";
		lineNumber += keepNumber;
		keepNumber = 0;
		return false;

	}
	else {
		fullString += hereWeAre;
		stringer(in.get());

		return true;
	}
	cout << "not sure how we got here." << endl;
	return true;

}

//I think I'm going to have to make this function recursive to be able to take in the
/*
string scanner::getaString() {
	string totalString = "\'";
	int keepLine = 0;
	char quote = '\'';
	char currentCharacter = ' ';
	//&& (currentChar != quote)

	char hereWeAre = ' ';
	if (hereWeAre == '\'') {
		while (in.peek() == '\'') {
			fullString += hereWeAre;
			in.get();
		}

	}

		while ((in.peek() != quote) ){
			if (in.peek() == '\n') {
				keepLine++;
			}
			if (in.eof()) {
				//undefined
				tokVec.push_back(Token(UNDEFINED, totalString, lineNumber));
				lineNumber += keepLine;
				return totalString;
			}
			else {
				currentCharacter = in.get();
				totalString += currentCharacter;
			}
			//totalString += in.get();
		}
		//string
		totalString += in.get();
		tokVec.push_back(Token(STRING, totalString, lineNumber));
		lineNumber += keepLine;
		return totalString;
}
*/

string scanner::getBlockComment() {
	string fullComment = "#";
	char getIt;
	int keepLines = 0;
	while (in.peek() != EOF) {
		getIt = in.get();
		if (getIt == '\n') {
			keepLines++;
		}
		if ((getIt == '|') && (in.peek() == '#')) {
			//full block comment
			in.get();
			fullComment += "|#";
			tokVec.push_back(Token(COMMENT, fullComment, lineNumber));
			lineNumber += keepLines;
			return fullComment;
		}
		else {
			fullComment += getIt;
		}
	}
	//undefined
	//in.unget();
	//in.get();
	//fullComment += in.get();
	tokVec.push_back(Token(UNDEFINED, fullComment, lineNumber));
	lineNumber += keepLines;
	return fullComment;
}


string scanner::printer() {
	string allTogether;
	for (unsigned int i = 0; i < tokVec.size(); i++) {
		Token gonnaPrint = tokVec[i];
		allTogether += gonnaPrint.toString() + ")\n";
	}
	cout << allTogether;
	int saveIt = tokVec.size();
	string tokNum = to_string(saveIt);
	cout << "Total Tokens = " << tokNum << endl ;
	return allTogether;
}


//as of right now, I need to fix the double quotes found on all things id.		I think I fixed this
//I also need to fix that it sends undefined characters through as numbers.		I think I fixed this too
//Need to make two adject single quotes an apostrophe.
