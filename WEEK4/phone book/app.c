#include <stdio.h>
#include <stdio_ext.h> // __fpurge(stdio);
#include <string.h>
#include "jrb.h"
#include "jval.h"
#define OUT "phonebook.txt"
#define strcut_newline(str) ((str)[strlen(str) - 1] == '\n')? (str)[strlen(str) - 1] = '\0':0;

#define MAX 50
void wait() {
  printf("\nEnter anything to return to menu: \n");
  getchar();
}

int main(){
  char name[MAX];
  long number;
  int choice;
  JRB tmp;
  JRB book = make_jrb();
  
  do{
    printf("1. Add phone\n");
    printf("2. Search phonenumber\n");
    printf("3. Delete key\n");
    printf("4. Print to file\n");
    printf("5. Exit\n");

    do{
      printf("Enter(1-5): ");
      scanf(" %d", &choice);
    }while(choice>5 || choice<1);

    switch (choice) {
      case 1:
        __fpurge(stdin);
        printf("Enter name: ");
        fgets(name, MAX-1, stdin);
      	strcut_newline(name);
        printf("Enter phone number: ");
        scanf("%ld", &number);
        insertNode(book, name, new_jval_l(number));
      	jrb_traverse(tmp, book);
        wait();
        break;

      case 2:
        __fpurge(stdin);
        printf("Enter name to search: ");
        fgets(name, MAX-1, stdin);
	      strcut_newline(name);

        searchPhone(book, name);
        wait();
        break;
      case 3:
        __fpurge(stdin);
        printf("Enter name to delete from tree\n");
        fgets(name, MAX-1, stdin);
        strcut_newline(name);
        deleteEntry(OUT,name, book); 
        jrb_print_file(OUT, book);
        wait();
      case 4:
        printf("Input data to file %s\n", OUT);
        jrb_print_file(OUT, book);
        wait();
        break;
    }

  }while (choice!=5);
  dropPhoneBook(book);
  return 0;
}
//end

