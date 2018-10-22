#include <stdlib.h>
#include "phoneBook.h"
#include <string.h>
#define INITIAL_SIZE 2
#define INCREMENTAL_SIZE 2

PhoneEntry makePhone(void* name, void* phone) {
	PhoneEntry res;
	res.key = strdup( (char*)name );
	res.value = malloc(sizeof(long));
	memcpy( res.value, phone, sizeof(long) );
	return res;
}
int comparePhone(void * key1, void* key2) {
	return strcmp((char*)key1, (char*)key2);
}

PhoneBook createPhoneBook(){
	PhoneBook pb = createSymbolTable(makePhone, comparePhone);
	return pb;
}

void dropPhoneBook(PhoneBook *pb){
	dropSymbolTable(pb);
}

void addPhoneNumber(char *name, long number, PhoneBook *pb){
	addEntry(name, &number, book);
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook *pb){
	return getEntry(name, pb);
}

char *getName(PhoneEntry e) {
	return (char *)getKey(e);
}

long getNumber(PhoneEntry e) {
	return *((long *)getValue(e));
}