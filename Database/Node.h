#pragma once

#include <map>
#include <string>


#include <set>
#include "Rule.h"


class Node {

public:
	int nodeNum;
	bool visited = false;
	int postorder;
	set <int> edges;
	Rule rul;
	Node();
	Node(int num, Rule rule);

	Rule getNode();

};