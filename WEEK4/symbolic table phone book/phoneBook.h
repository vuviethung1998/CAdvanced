#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_
#include "symtab.h"
typedef Entry PhoneEntry;
typedef SymbolTable PhoneBook;
//need to extend if reach

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);//memcpy
void addPhoneNumber(char * name, long number, PhoneBook* book);
PhoneEntry * getPhoneNumber(char * name, PhoneBook *book);			

char *getName(Entry e);
long getNumber(Entry e);

#endif