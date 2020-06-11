
#include "Parameter.h"

parameter::parameter() {

}


parameter::parameter(Token paramTok) {
	param = paramTok;
	isTok = true;
}
parameter::parameter(string express) {
	paramEx = express;
	isEx = true;
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
