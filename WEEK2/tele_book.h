#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "reverseWord.h"

typedef struct pBook pBook;

struct pBook{
  char name[50];
  char tel[15];
  char reverseName[50];
};

int numOfRec(char *fn);
void addRec(struct pBook pBookList[], struct pBook a, int *start, int size );
void printList(struct pBook *pBookList, int size);
struct pBook *getData(char *fn, struct pBook *pBookList, int size);
int name_compare(struct pBook a, struct pBook b);
int generic_compare(const void *a, const void *b);
void exch(void *x, void *y, int size);
void sort3way (void *a, int size, int l, int r,int(*generic_compare)(const void*, const void *));
struct pBook *dumpArray(struct pBook a[],int size);
int search(  void* buf,int size,int l, int r, void * item,int(*generic_compare)(const void*, const void *));
void findLastName(char *s, struct pBook pBookList[], int size);

//code
int numOfRec(char *fn){
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

//them tu txt vao list struct
void addRec(struct pBook pBookList[], struct pBook a, int *start, int size ){
  int *cur = start;
  if((*cur)<size){
    pBookList[*cur] = a;
    (*cur) ++;
    *start = *cur;
    return;
  }
  else return;
}

void printList(struct pBook *pBookList, int size){
  for(int i =0; i <size; i++){
    printf("%-20s%20s\n", pBookList[i].name, pBookList[i].tel);
  }
}

//xu ly du lieu tu file txt
struct pBook *getData(char *fn, struct pBook *pBookList, int size){
  FILE *f = fopen(fn, "r+");

  if(f == NULL){
    printf("Cannot open file name %s\n",fn);
    return NULL;
  }

  int startNum = 0;
  int *num = &startNum;

  while(!feof(f)){
    struct pBook temp;
    fscanf(f, "%[^\t]\t%[^\n]\n",temp.name,temp.tel);
    strcpy(temp.reverseName, temp.name);
    reverseWords(temp.reverseName);
    addRec(pBookList, temp, num, size);
  }

  return pBookList;
}

int compare(struct pBook a, struct pBook b){
  if (strcmp(a.reverseName, b.reverseName) > 0) {
		return(1);
	}
	else if (strcmp(a.reverseName, b.reverseName) == 0 ) {
		return(0);
	}
	
	return(-1);
}

int generic_compare(const void *a, const void *b) {
  struct pBook x = *((struct pBook*)a); 
  struct pBook y = *((struct pBook*)b);
  int cp = compare(x,y);

  return (cp == 0 ? 0: (cp == 1? 1 : -1));
}

void exch(void *x, void *y, int size){
  char *first = (char *) x;
  char *last = (char *) x +size;
  char *res = (char *) y;
  char tmp;
  for(;first!= last; first ++) {
    tmp = *first; *first = *res; *res = tmp;
    res ++;  
  }
}


void sort3way (void *a, int size, int l, int r,int(*generic_compare)(const void*, const void *) ){
  if(r<= l ) return;
  int i = l-1, j =r;
  int p = l -1, q = r;

  while(1){
    while (generic_compare((char *)a + (++i)*size, (char *)a + r*size)<0);      
    while (generic_compare((char *)a + r *size, (char *)a + (--j)*size)<0) if(j == l) break;
  if( i >= j) break;
  exch((char *)a+ i*size, (char *)a+ j *size ,size);
if(generic_compare((char *)a + i *size, (char *)a+ r *size)== 0){
  exch((char *)a + (++p)*size, (char *)a+i *size, size);
  if(generic_compare((char *)a + j *size, (char *)a+ r *size)== 0) exch((char *)a + (--q)*size, (char *)a+j *size, size);
 }
}

exch((char *)a + i*size, (char *)a+ r*size, size);
j = i -1;
i = i+1;

for(int k = l; k <= p; k++) exch((char *)a + k*size, (char *)a+ (j--) *size, size);
for(int k = r-1; k >= q; k--) exch((char *)a + k*size, (char *)a+(i++) *size, size);

sort3way(a, size,l ,j,generic_compare);
sort3way(a, size ,i,r,generic_compare);
}

struct pBook *dumpArray(struct pBook a[],int size){
	struct pBook *newArr = (struct pBook *)malloc(sizeof(struct pBook)*size);
	memcpy(newArr, a, sizeof(struct pBook)*size);	

	return newArr;
}

int search(  void* buf,int size,int l, int r, void * item,int(*generic_compare)(const void*, const void *)) {
	if (r < l) return -1;
	int i = (l + r)/2;
	int res = generic_compare( item, (char*)buf+(size*i) );
	if (res==0)
		return i;
	else if (res < 0)
		return search(buf, size, l, i-1, item, generic_compare);
	else
		return search(buf, size, i+1, r, item, generic_compare);
}

void findLastName(char *s, struct pBook pBookList[], int size){

}
