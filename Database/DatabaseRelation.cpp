

#include "DatabaseRelation.h"

DatabaseRelation::DatabaseRelation() {

}


DatabaseRelation::DatabaseRelation(string nam, Scheme rel, set<Toople> tup) {
	name = nam;
	headers = rel;
	allData = tup;
}
