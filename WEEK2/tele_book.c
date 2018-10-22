#include <stdio.h>
#include "tele_book.h"
#define FNAME "phonebook.txt"


int main() {
  int size = numOfRec(FNAME);

  struct pBook *a1, *a2;
  a1= getData(FNAME, a1, size);
  a2 = dumpArray(a1, size);

  sort3way(a2, sizeof(struct pBook), 0, size -1, generic_compare);
  printList(a2, size);

  char name[50];
  printf("Nhap ten ban muon tim: ");
  gets(name);
  /*
  void *item = malloc(sizeof(char)*50);
  item = (void *)name;

  int res = search(a2, sizeof(char)*50,0, size -1,item, generic_compare );

  printf("Ban %s o vi tri %d\n",name, res);*/
  
  return 0;
}
