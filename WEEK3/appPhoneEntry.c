#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phoneEntry.h"

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

Entry makePhone(void *name, void *number){
  Entry res;
  res.key = strdup((char *)name);
  res.value =malloc(sizeof(long));
  memcpy(res.value, number, sizeof(long));

  return res;
}

int comparePhone(void *key1, void *key2){
  return strcmp((char *)key1,(char *)key2);
}

int main(){
  char name[50];
  long number;
  int choice;

  SymbolTable pb = createSymbolTable(makePhone,comparePhone);

  do{
    printf("1. Add new entry\n");
	printf("2. Lookup phone entry\n");
    printf("3. 	Quit\n");
    scanf("%d", &choice);

	switch(choice) {
	case 1:
	  printf("Name: \n"); scanf("%s", name);
	  printf("Number\n"); scanf("%ld", &number);
	  addEntry((void*)name, (void *)number, &pb);
	  break;
	case 2:
	  	printf("Name:\n");scanf("%s", name);
		Entry * e = getEntry((void *)name, &pb);
		if(e == NULL) printf("Not found\n");
		else printf("Number: %ld\n",*((long *)e->value));
		printf("Number: \n"); scanf("%ld", &number);
	        addEntry((void *)name,(void *)number, &pb);
		break;
	}
  }while(choice != 3);
  dropSymbolTable(&pb);
}
