#ifndef mainly_H
#define mainly_H


#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <stdlib.h>
#include <cstdlib>
#include <array>
#include <stack>
#include <stdexcept>
#include "Token.h"
#include "scanner.h"
using namespace std;




int main(int argc, char* argv[]) {

	string file = argv[1];
	scanner scan1(file);
	//ask user for filename
	//cout << "got here" << endl;
	scan1.Scan();
	//print tokens out
	string toPrint;
	toPrint = scan1.printer();

	return 0;
}



#endif
