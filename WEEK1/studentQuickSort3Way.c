#include <stdio.h>
#include "studentQuickSort.h"
#define FNAME "duLieuHocSinh.txt"

int main(){
    int size = numOfRecord(FNAME);
	struct Student *a1 , *a2;
	a1= getData(FNAME, a1, size);
	a2 = dumpArray(a1, size);

	//sort3way(a2, 0, size -1);//sor
    sort2way(a2, 0, size -1);
    printList(a2, size);


    return 0;
}