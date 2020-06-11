

#include "Node.h"

Node::Node() {

}

Node:: Node(int num, Rule rule) {

	nodeNum = num;
	rul = rule;
	postorder = 0;

}

Rule Node::getNode() {
	return rul;
}