#include <stdlib.h>
#include "phoneEntry.h"
#include <string.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

SymbolTable createSymbolTable(Entry (*makeNode) (void *, void*), int(*compare)(void *, void*)){
  SymbolTable pb;
  pb.entries = (Entry *)malloc(INITIAL_SIZE *sizeof(Entry));
  pb.total = 0;
  pb.size = INITIAL_SIZE;
  return pb;
}

void dropSymbolTable(SymbolTable *tab){
  free(tab->entries);
}

Entry *getEntry(void *name, SymbolTable *book){
  int i;
  for(i = 0; i < book->total; i++) 
    if(strcmp(name, book->entries[i].key) == 0) break;
  if(i<book->total) return &(book->entries[i]);
  else return NULL;  
}
 
void addEntry(void *name, void *number, SymbolTable *book) {
  Entry *e = getEntry(name, book);
  Entry *new_entries;
  if(e== NULL){/*Trong truong hop ko tim thay ket qua*/
    if(book->total >= book->size) {
      new_entries =(Entry *)malloc((book->size + INCREMENTAL_SIZE)*sizeof(Entry));
      memcpy(new_entries, book->entries, book->total*sizeof(Entry));
	     book->entries = new_entries;
	     book->size += INCREMENTAL_SIZE;
    }
    //memcpy(book->entries[book->total].key, name, sizeof(char) * 20);
    strcpy((book->entries[book->total]).key, name);
    book->entries[book->total].value = &number;
    book->total ++;
  }
  else e->value = &number;
}


