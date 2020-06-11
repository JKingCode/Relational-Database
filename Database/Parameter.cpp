
#include "Parameter.h"

parameter::parameter() {

}


parameter::parameter(Token paramTok) {
	if (paramTok.getType() == ID) {
		isConst = false;
	}
	else if (paramTok.getType() == STRING) {
		isConst = true;
	}
	param = paramTok;
	isTok = true;
}

parameter::parameter(string express) {
	paramEx = express;
	isEx = true;
}

bool parameter:: getConst() {
	return isConst;
}

string parameter::toString() {
	string returnable = "";
	if (isTok == true) {
		returnable = param.getVal();
	}
	else if (isEx == true) {
		returnable += paramEx;
	}
	else {
		//how I get here?
	}
	return returnable;
}
