#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pBook{
	char ho[10];
	char dem[10];
	char ten[10];
	char phone[20];
};


int numOfRecord(char *fn){
	FILE *f = fopen(fn, "r+");
	if(f == NULL){
		printf("Cant open file %s\n", fn);
		return -1;
	}

	int i = 0;
	while(!feof(f)){
		char ch = fgetc(f);
		if(ch == '\n')	i++;
	}
	fclose(f);

	return i+1;
}

void addAddress(struct pBook pBookList[],struct pBook a, int *start,int size) {
	int *cur = start;
	if((*cur) < size){	
		pBookList[*cur] = a;
		(*cur) ++;
		*start = *cur;
		return;
	}
	else return;
}

int pBook_Compare(const void * a,const void * b){
	struct pBook *sA = (struct pBook *)a; 
	struct pBook *sB = (struct pBook *)b;

	int check1, check2;

	check1 = strcmp(sA->ten, sB->ten);
	check2 = strcmp(sA->dem, sB->dem);
	if(check1 == 0) {
		if(check2 == 0) return 0;
		return ((check2 > 0) ? 1 : -1);
	}

	return ((check1 >0)? 1 : -1);
}

//tao list hs DONE
struct pBook *getData(char *fn,struct pBook *pBookList, int size) {
	FILE *f = fopen(fn, "r+");
	if(f == NULL ){
		printf("Cannot open file %s\n", fn);
		return NULL;
	}

	int startNum = 0;
	int *num = &startNum;
	while(!feof(f)){
		struct pBook tempStd;
		fscanf(f,"%s %s %[^\t]\t%[^\n]",pBookList->ho,pBookList->dem, pBookList->ten,pBookList->phone);
		addAddress(pBookList,tempStd, num, size);
	}

	return pBookList;
}

struct pBook *dumpArray(struct pBook a[],int size){
	struct pBook *newArr = (struct pBook *)malloc(sizeof(struct pBook)*size);
	memcpy(newArr, a, sizeof(struct pBook)*size);	

	return newArr;
}

void printList(struct pBook *pBookList, int size) {
	for (int i = 0; i < size; ++i)
	{
		printf("%s %s %s\t%s\n", pBookList[i].ho,pBookList[i].dem,pBookList[i].ten,pBookList[i].phone);
	}
}