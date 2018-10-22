#ifndef _JVAL_H_
#define _JVAL_H_
#include <string.h>
#include <time.h>
typedef union {
    int i;
    long l;
    float f;
    double d;
    void *v;
    char *s;
    char c;
    short sh;
 } Jval;

Jval new_jval_i(int i){ Jval j; j.i = i; return j; }

int jval_i(Jval j) {return j.i;}


//sort gen
void exch(Jval *x, Jval *y){
  Jval tmp = *x;
  *x = *y;
  *y = tmp;
}

int compare_i(Jval* a, Jval* b) {
  if ( jval_i(*a)==jval_i(*b) ) return 0;
  if ( jval_i(*a) < jval_i(*b) ) return -1;
  else return 1;
}

void sort_gen(Jval *a,int l, int r, int (*generic_compare)(Jval*, Jval*)){
	if(r<= l ) return;
    int i = l-1, j =r;
    int p = l -1, q = r;
  
  	while(1){
    while (generic_compare(a[++i] , a[r] )<0);      
    while (generic_compare(a[r] , a[--j] <0)) if(j == l) break;
  	if( i >= j) break;
  		exch(a[i], a[j]);
  	if(generic_compare(a[i], a[r])== 0){
  		exch(a[++p], a[i]);
  	if(generic_compare(a[j], a[r])== 0) exch(a[--q], a[j]);
	  }
	}

	exch(a[i], a[r]);
	j = i -1;
	i = i+1;

	for(int k = l; k <= p; k++) exch(a[k], a[j--]);
	for(int k = r-1; k >= q; k--) exch(a[k], a[i++]);

	sort_gen(a, l ,j,generic_compare);
	sort_gen(a ,i,r,generic_compare);
}

//sort all
void sort_i (Jval a[], int l, int r) {
  sort_gen(a, l,r, compare_i);
}

int search_i (Jval a[], int l, int r, int x) {
  return search_gen(a, sizeof(int), l, r, y, compare_i);
}

int search_gen ( Jval a[], int l, int r, Jval *item, int(*generic_compare)(Jval*, Jval*)){
	if (r < l) return -1;
	int i = (l + r)/2;
	int res = generic_compare( item, a[i] );
	if (res==0) return i;
	else if (res < 0)
		return search_gen(a, l, i-1, item, generic_compare);
	else
		return search_gen(a, i+1, r, item, generic_compare);
}

Jval* create_array_i (int n) {
	Jval * array = (Jval *) malloc(sizeof(Jval)*n);
	for (int i = 0; i < n; i++) array[i] = new_jval_i( rand()%100 );
	return array;
}


Jval *dumpArray_i(Jval a[],int size){
	Jval *newArr;
	newArr = (Jval *)malloc(sizeof(Jval)*size);
	memcpy(newArr, a, sizeof(Jval)*size);	

	return newArr;
}

void printList(Jval *a, int size){
	for(int i =0; i < size; i ++) 
		printf("%d\n", jval_i(a[i]));
}

#endif
// Jval new_jval_l(long l){ Jval j; j.l = l; return j; }
// Jval new_jval_f(float f){ Jval j; j.f = f; return j; }
// Jval new_jval_d(double d){ Jval j; j.d = d; return j; }
// Jval new_jval_v(void *v){ Jval j; j.v = v; return j; }
// Jval new_jval_s(char *s){ Jval j; strcpy(j.s,s); return j; } 
// Jval new_jval_c(char c) { Jval j; j.c = c; return j; }
// Jval new_jval_sh(short sh) {Jval j; j.sh = sh; return j; }
// double jval_d(Jval j){return j.d;}
// long jval_l(Jval j) {return j.l;}
// float jval_f(Jval j ){return j.f;}
// char jval_c(Jval j){return j.c;}
// short jval_sh(Jval j){return j.sh;}
// char* jval_s(Jval j){return j.s;}
// void* jval_v(Jval j){return j.v;}
//sort long
// void sort_l(Jval a[], int l, int r ){
//   sort_gen(a , sizeof(long),l,r, compare_l);
// }
// //sort float
// void sort_f(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(float), l, r, compare_f);
// }
// //sort double
// void sort_d(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(double) ,l, r, compare_d);
// }
// //sort void
// void sort_v(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(void *),l,r, compare_v);?UT
// }
// //void string
// void sort_s(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(char)*50,l,r, compare_s);
// }
// //void char
// void sort_c(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(char),l,r, compare_c);
// }
// //void short
// void sort_sh(Jval a[], int l, int r ){
//   sort_gen(a,sizeof(short),l,r, compare_sh);
// }


//compare 

// int compare_l(Jval* a, Jval* b){
//   if ( jval_l(*a)==jval_l(*b) ) return 0;
//   if ( jval_l(*a) < jval_l(*b) ) return -1;
//   else return 1;
// }
// int compare_f(Jval* a, Jval* b){
//   if ( jval_f(*a)==jval_f(*b) ) return 0;
//   if ( jval_f(*a) < jval_f(*b) ) return -1;
//   else return 1;
// }
// int compare_d(Jval* a, Jval* b){
//   if ( jval_d(*a)==jval_d(*b) ) return 0;
//   if ( jval_d(*a) < jval_d(*b) ) return -1;
//   else return 1;
// }

// int compare_v(Jval* a, Jval* b){
//   if ( jval_d(*a)==jval_d(*b) ) return 0;
//   if ( jval_d(*a) < jval_d(*b) ) return -1;
//   else return 1;
// }

// int compare_s(Jval* a, Jval* b){
//   if ( jval_s(*a)==jval_s(*b) ) return 0;
//   if ( jval_s(*a) < jval_s(*b) ) return -1;
//   else return 1;
// }
// int compare_c(Jval* a, Jval* b){
//   if ( (int)jval_c(*a)== (int)jval_c(*b) ) return 0;
//   if ( (int)jval_c(*a) < (int)jval_c(*b) ) return -1;
//   else return 1;
// }
// int compare_sh(Jval* a, Jval* b){
//   if ( jval_sh(*a)==jval_sh(*b) ) return 0;
//   if ( jval_sh(*a) < jval_sh(*b) ) return -1;
//   else return 1;
// }

//search

// int search_l (Jval a[], int l, int r, long x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a, sizeof(long),l, r, y, compare_l);;
// }
// int search_f (Jval a[], int l, int r, float x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a, sizeof(float),l, r, y, compare_f);
// }
// int search_d (Jval a[], int l, int r, double x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a,sizeof(double) ,l, r, y, compare_d);
// }
// int search_v (Jval a[], int l, int r, void * x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a, sizeof(void *),l, r, y, compare_v);
// }
// int search_s (Jval a[], int l, int r, char * x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a,sizeof(char) * 50, l, r, y, compare_s);
// }
// int search_c (Jval a[], int l, int r, char x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a,sizeof(char) ,l, r, y, compare_c);
// }
// int search_sh (Jval a[], int l, int r, short x){
// 	Jval * y = (Jval *)new_jval_i(x);
//   return search_gen(a,sizeof(short), l, r,y, compare_sh);
// }

