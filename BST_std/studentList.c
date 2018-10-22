#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reverseWord.h"
#include "BST_studentList.h"

void clear_buffer() {
	while (getchar() != '\n')
		;
	return;
}

void getData(char *fn, BSTNode **root) {

	FILE *f = fopen(fn, "r");

	if (f == NULL) {
		printf("Can not open file %s \n", fn);
		return;
	}

	dataTypeBST tempData;

	while (!feof(f)) {
		fgets(tempData.name, 50, f);
		tempData.name[ strlen(tempData.name) - 1 ] = '\0';

		strcpy(tempData.reverseName, tempData.name);
		reverseWords(tempData.reverseName);

		insertBST(root, NULL, tempData);
	}

	
	return;
}

int main() {

	BSTNode *root;
	BST_init(&root);

	int op;

	do {
		printf("1 . Get data from file studentlist.txt and create binary search tree\n");
		printf("2 . print sorted student list \n");
		printf("3 . Search by name \n");
		printf("4 . Exit program! \n");
		printf("Option : ");
		scanf("%d", &op);
		clear_buffer();

		switch (op) {
		case 1: {
			getData("studentList.txt", &root);
			break;
		}

		case 2: {
			inorder(root);
			break;
		}
			
		case 3: {
			dataTypeBST tempData; // create temp data from input name

			printf("What's name do you want to search : ");
			fgets(tempData.name, 50, stdin);
			tempData.name[ strlen(tempData.name) - 1 ] = '\0';

			strcpy(tempData.reverseName, tempData.name);
			reverseWords(tempData.reverseName);

			BSTNode *p = search(root, tempData);
			if (p != NULL) {
				
				printf("Name founded : %s \n", p->data.name);
			}
			else {
				printf("Name not found!\n");
			}

			break;
		}
		case 4: {
			printf("Goodbye! \n");
			break;
		}
		}
	} while (op != 4);
	
	return(0);
}
