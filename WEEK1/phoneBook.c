#include "phoneBook.h"
#include <stdio.h>
#define FNAME "phoneBook.txt"

int main(){
	int size = numOfRecord(FNAME);
	printf("%d\n", size);
	struct pBook *pBookList = (struct pBook *)malloc(sizeof(struct pBook)* size);
	pBookList = getData(FNAME, pBookList, size);

	qsort(pBookList, size, sizeof(struct pBook), pBook_Compare);

	printList(pBookList,size);
	return 0;

}