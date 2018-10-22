#include <stdio.h> 
#include "btree/inc/btree.h"

int main() {
	BTA *dict;
	char key[ZKYLEN];
	int val;

	btinit();
	dict = btcrt("test.data", 0 , FALSE);
	binsky(dict, "a", 123);
	binsky(dict, "b", 345);

	btpos(dict, ZSTART);
	while(bnxtky(dict, key, &val) == 0) 
		printf("%s -> %d\n", key, val);

	btcls(dict);

	return 0;
}
