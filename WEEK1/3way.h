#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SMALL_NUMBER 20
#define BIG_NUMBER 1000000000

void exch(int a[], int i,int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void sort2way(int a[], int l,int r){
	if(r<= l ) return;
	int i = l-1, j =r;

	while(1){
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if(j == l) break;
		if( i >= j) break;
		exch(a, i ,j);
	}
	exch(a, i ,r);
	j = i -1;
	i = i+1;

	sort2way(a, l, j);
	sort2way(a, i, r);	
}


void sort3way (int a[], int l, int r){
	if(r<= l ) return;
	int i = l-1, j =r;
	int p = l -1, q = r;

	while(1){
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if(j == l) break;
		if( i >= j) break;
		exch(a, i ,j);
		if(a[i] == a[r]) exch(a , ++p, i);
		if(a[j] == a[r]) exch(a , --q, j);
	}
	exch(a, i ,r);
	j = i -1;
	i = i+1;

	for(int k = l; k <= p; k++) exch(a, k , j--);
	for(int k = r-1; k >= q; k--) exch(a, k , i++);

	sort3way(a, l ,j);
	sort3way(a,i,r);
}



int *createArray(int size){
	int *arr;
	arr = (int *)malloc(sizeof(int)*size);

	for(int i = 0; i< size; i++){
		arr[i] = rand()%10;
	} 

	return arr;
}


int *dumpArray(int a[],int size){
	int *newArr;
	newArr = (int *)malloc(sizeof(int)*size);
	memcpy(newArr, a, sizeof(int)*size);	

	return newArr;
}

