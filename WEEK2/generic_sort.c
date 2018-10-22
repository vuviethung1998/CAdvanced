#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#define SMALL_NUMBER 20
#define BIG_NUMBER 1000000000
//ham exch
//create array
//dump array
//ham sort3way
// search
int generic_compare(const void *a, const void *b){
  int x = *((int *)a);
  int y = *((int *)b);
  return ( x == y ? 0:( x > y ? 1:-1));
}

void exch(void *x, void *y, int size) {
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


int *createArray(int size){
	int *arr;
	arr = (int *)malloc(sizeof(int)*size);

	for(int i = 0; i< size; i++){
		arr[i] = rand()%10;
	} 

	return arr;
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

int *dumpArray(int a[],int size){
	int *newArr;
	newArr = (int *)malloc(sizeof(int)*size);
	memcpy(newArr, a, sizeof(int)*size);	

	return newArr;
}
int main() {
  	struct timeval start, stop;

	double elapsed;
	int *a1 , *a2;
	int i;
	srand(time(0));
	a1= createArray(SMALL_NUMBER);
	a2 = dumpArray(a1, SMALL_NUMBER);

	gettimeofday(&start, NULL);
	sort3way(a2,sizeof(int), 0, SMALL_NUMBER -1,generic_compare);//sort
	gettimeofday(&stop, NULL);
	elapsed = (double)(stop.tv_usec -start.tv_usec)/1000000 +(double)(stop.tv_usec -start.tv_usec);
	printf("sort3way: %f\n" , elapsed);	
	
	gettimeofday(&start, NULL);
	void *item = malloc(sizeof(int));
        *((int*)item) = -20;
	int res = search (a2, sizeof(int), 0, SMALL_NUMBER-1, item , generic_compare);
	printf("So 5 o vi tri: %d", res);
	return 0;  
}
