#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "duLieuHocSinh.txt"
#define MAX_ITEM 50

typedef struct Student Student;

struct Student{
	char name [20];
	int id;
	float score;
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

//them hoc sinh vao list
void addStudent(struct Student stdList[],struct Student a, int *start,int size) {
	int *cur = start;
	if((*cur) < size){	
		stdList[*cur] = a;
		(*cur) ++;
		*start = *cur;
		return;
	}
	else return;
}

//DONE
void printList(struct Student *stdList, int num) {
	for(int i =0; i <num; i++) {
		printf("%-20s%20d%30.2f\n",stdList[i].name, stdList[i].id,stdList[i].score);
	}
}

//tao list hs DONE
struct Student *getData(char *fn,struct Student *stdList, int size) {
	FILE *f = fopen(fn, "r+");
	if(f == NULL ){
		printf("Cannot open file %s\n", fn);
		return NULL;
	}
	int startNum = 0;
	int *num = &startNum;
	while(!feof(f)){
		struct Student tempStd;
		fscanf(f,"%[^\t]\t%d\t%f\n",tempStd.name,&(tempStd.id),&(tempStd.score));
		addStudent(stdList,tempStd, num, size);
	}

	return stdList;
}

int studentCompare (const void * a, const void * b)
{

  	struct Student *sA = (struct Student *)a;
  	struct Student *sB= (struct Student *)b;

	if(sA->id == sB->id) return 0;

	return(sA->id > sB->id ? 1 : -1);
}


int main()
{
	int n = numOfRecord(FNAME);
	printf("%d\n", n);
	struct Student *stdList = (struct Student *)malloc(sizeof(struct Student)* n);
	stdList = getData(FNAME,stdList, n);

	qsort(stdList, n, sizeof(struct Student), studentCompare);

	printList(stdList,n);
	return 0;
}
