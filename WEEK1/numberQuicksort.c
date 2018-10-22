#include <stdio.h>
#include <stdlib.h>

int int_compare(void const *x, void const *y){
	int n, m;
	m = *((int*) x);
	n = *((int*) y);

	if(m == n) return 0;
	return (m >n ? 1 : -1);
}

int *createArray(int size){
	int *arr;
	arr = (int *)malloc(sizeof(int)*size);

	for(int i = 0; i< size; i++){
		arr[i] = rand()%10;
	} 

	return arr;
}
int main(){
	int *a = createArray(10);
	qsort(a, 10,sizeof(int),int_compare);

	for(int i =0; i< 10; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}