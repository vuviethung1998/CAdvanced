#include <stdio.h>
#include <stdio_ext.h>
#include "phoneBook.h"
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5
int main(){
	char name[50];
	long number;
	int choice;
	PhoneBook pb = createPhoneBook();

	do{
		printf("1. Add new entry\n");
		printf("2. Lookup phone entry\n");
		printf("3. 	Quit\n");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				__fpurge(stdin);
				printf("Name: \n"); scanf("%s", name);
				printf("Number\n"); scanf("%ld", &number);
				addPhoneNumber(name, number, &pb);
				break;
			case 2:
				__fpurge(stdin);
				printf("Name:\n");scanf("%s", name);
				PhoneEntry * e =getPhoneNumber(name, &pb);
				if(e == NULL) printf("Not found\n");
				else printf("Number: %ld\n", e->number);
				printf("Number: \n"); scanf("%ld", &number);
				addPhoneNumber(name, number, &pb);
				break;
		}
	} 
	while(choice != 3);

	dropPhoneBook(&pb);
	return 0;
}