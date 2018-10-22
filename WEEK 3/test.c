#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	void *lv;
	char l[50];
	strcpy(l, "arafa afasfsaaf");
	lv = l;

	char l2[50];
	strcpy(l2, (char *)l);
	
	printf("%s\n", l2);

	return 0;
}