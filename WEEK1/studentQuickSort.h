#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define FNAME "duLieuHocSinh.txt"
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


void exch(struct Student stdList[], int i, int j){
	struct Student tempStd = stdList[i];
	stdList[i] = stdList[j];
	stdList[j] = tempStd;
}

void sort3way (struct Student a[], int l, int r){
	if(r<= l ) return;
	int i = l -1, j =r;
	int p = l -1, q = r;

	while(1){
		while (a[++i].id < a[r].id);
		while (a[r].id < a[--j].id) if(j == l) break;
		if( i >= j) break;
		exch(a, i ,j);
		if(a[i].id == a[r].id) exch(a , ++p, i);
		if(a[j].id == a[r].id) exch(a , --q, j);
	}
	exch(a, i ,r);
	j = i -1;
	i = i+1;

	for(int k = l; k <= p; k++) exch(a, k , j--);
	for(int k = r-1; k >= q; k--) exch(a, k , i++);

	sort3way(a, l ,j);
	sort3way(a,i,r);
}

void sort2way(struct Student a[], int l,int r){
	if(r<= l ) return;
	int i = l-1, j =r;

	while(1){
		while (a[++i].id < a[r].id);
		while (a[r].id < a[--j].id) if(j == l) break;
		if( i >= j) break;
		exch(a, i ,j);
	}
	exch(a, i ,r);
	j = i -1;
	i = i+1;

	sort2way(a, l, j);
	sort2way(a, i, r);	
}


struct Student *dumpArray(struct Student a[],int size){
	struct Student *newArr = (struct Student *)malloc(sizeof(struct Student)*size);
	memcpy(newArr, a, sizeof(struct Student)*size);	

	return newArr;
}
