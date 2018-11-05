#include <stdlib.h>
#include "symtab.h"
#include <string.h>

#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 2

typedef struct {
  void *key;
  void *value;
} Entry;

typedef struct {
  Entry * entries;
  int size, total;
  Entry (*makeNode)(void*,void*);
  int (*compare)(void*,void*);
} SymbolTable;


SymbolTable createSymbolTable(Entry (*makeNode) (void *, void*), int(*compare)(void *, void*)){
  SymbolTable pb;
  pb.entries = (Entry *)malloc(INITIAL_SIZE *sizeof(Entry));
  pb.total = 0;
  pb.size = INITIAL_SIZE;
  pb.makeNode =makeNode;
  pb.compare = compare;

  return pb;
}

void dropSymbolTable(SymbolTable *pb){
  int i;
  for(i = 0; i <pb.total; i ++){
    free(pb->entries[i].key);
    free(pb->entries[i].value);
  }
  free(pb->entries);
}

void addEntry(void *key, void *value, SymbolTable *tb) {
  Entry *e = getEntry(key, tb);
  Entry *new_entries;
  if(e== NULL){/*Trong truong hop ko tim thay ket qua*/
    if(tb->total >= tb->size) {
      new_entries =(Entry *)malloc((tb->size + INCREMENTAL_SIZE)*sizeof(Entry));
      memcpy(new_entries, tb->entries, tb->total*sizeof(Entry));
	     tb->entries = new_entries;
	     tb->size += INCREMENTAL_SIZE;
    }
    //make new entry n put new entry to the end of symbol table
    tb->entries[tb->total] = tb->makeNode(key,value);
    //memcpy(book->entries[book->total].key, name, sizeof(char) * 20);
    tb->total ++;
  }
}

Entry *getEntry(void *key, SymbolTable *tb){
  int i;
  for(i = 0; i < tb->total; i++) 
    if(tb->compare(key, (tb->entries[i]).key) == 0) break;
  if(i<tb->total) return &(tb->entries[i]);
  else return NULL;  
}

void *getKey(Entry e){
  return e.key;
}

void *getValue(Entry e) {
  return e.value
}