#ifndef _PHONE_ENTRY_H
#define _PHONE_ENTRY_H

struct EntryStr;
struct SymbolTableStr;
typedef struct SymbolTableStr SymbolTable;
typedef struct EntryStr Entry;


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

SymbolTable createSymbolTable(Entry (*makeNode) (void *, void*), int(*compare)(void *, void*));
void dropSymbolTable(SymbolTable *tab);
void addEntry(void *key, void *value, SymbolTable *book);
Entry *getEntry(void *key, SymbolTable *book);
void *getKey(Entry e);
void *getValue(Entry e);


#endif