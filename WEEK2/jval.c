#include <stdio.h>
#include <stdlib.h>
#include "jval.h"
#define SMALL_NUMBER 50
int main() {
  	struct timeval start, stop;

	double elapsed;
	Jval *a1 , *a2;
	int i;
	srand(time(0));
	a1= create_array_i(SMALL_NUMBER);
	a2 = dumpArray(a1, SMALL_NUMBER);
	sort_i(a2, 0, SMALL_NUMBER - 1);

	printList(a2, SMALL_NUMBER -1);
	//Jval *item = malloc(sizeof(int));
        //*((int*)item) = -20;
	//int res = search (a2, sizeof(int), 0, SMALL_NUMBER-1, item , generic_compare);
	//printf("So 5 o vi tri: %d", res);
	return 0;  
}
  
