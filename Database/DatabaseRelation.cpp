

#include "DatabaseRelation.h"

DatabaseRelation::DatabaseRelation() {

}


DatabaseRelation::DatabaseRelation(string nam, Scheme rel, set<Toople> tup) {
	name = nam;
	headers = rel;
	allData = tup;
}

/*
//need to move this over to the relation class
Relation DatabaseRelation::join(Relation result, Relation toJoin1, Relation toJoin2) {
	Relation toReturn = result;
	vector<int> sameIndex1;
	vector<int> sameIndex2;

	//finding the 
	for (int i = 0; i < toJoin1.getName().size(); i++) {
		for (int j = 0; j < toJoin2.getName().size(); j++) {
			if (toJoin1.getName()[i] == toJoin2.getName()[j]) {
				sameIndex1.push_back[i];
				sameIndex2.push_back[j];
			}
		}
	}

	//trying to join the two tuples
	for (Toople search1 : toJoin1.getTup()) {
		for (Toople search2 : toJoin2.getTup()) {
			bool canAdd = true;
			vector<string> tup1 = search1;
			vector<string> tup2 = search2;
			//checking to see if the tuple values are equal
			for (int i = 0; i < sameIndex1.size(); i++) {
				if (tup1[sameIndex1[i]] == tup2[sameIndex2[i]]) {
					canAdd == true;
				}
				else {
					canAdd == false;
				}
			}
			//adding tuples to the relation
			if (canAdd == true) {
				Toople toAdd = search1;
				for (int i = 0; i < search2.size(); i++) {
					bool skip = false;
					for (int j = 0; j < sameIndex2.size(); j++) {
						if (i == sameIndex2[j]) {
							skip = true;
						}
					}
					if (skip) {
						continue;
					}
					else {
						toAdd.push_back(search2[i]);
					}
				}
				toReturn.addTuple(toAdd);

			}
		}
	}


}
*/