#include <stdlib.h>
#include "phoneBook.h"
#include <string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

PhoneBook createPhoneBook(){
	PhoneBook pb;
	pb.entries = (PhoneEntry *)malloc(INITIAL_SIZE*sizeof(PhoneEntry));
	pb.total = 0;
	pb.size = INITIAL_SIZE;
	return pb;
}

void dropPhoneBook(PhoneBook *pb){
	free(pb->entries);
}

void addPhoneNumber(char *name, long number, PhoneBook *pb){
	PhoneEntry *e = getPhoneNumber(name , &pb);
	PhoneEntry *new_entries;
	if(e == NULL) {/*Trong t hop ko tim thay ten thi tao ten moi*/
		if(pb->total >= pb->size){
			new_entries = (PhoneEntry *)malloc((pb->size + INCREMENTAL_SIZE)*sizeof(PhoneEntry));
			memcpy(new_entries, pb->entries,pb->total*sizeof(PhoneEntry));
			pb->entries = new_entries;
			pb->size += INCREMENTAL_SIZE;
		}
		strcpy((pb->entries[pb->total]).name,name);
		(pb->entries[pb->total]).number = number;
		pb->total ++;
	}else e->number = number;// sua so
}

PhoneEntry *getPhoneNumber(char *name, PhoneBook *pb){
	int i;
	for(i = 0; i < pb->total; i++){
	  if(strcmp(name, (pb->entries[i]).name) == 0) break;
	  if(i < pb->total) return &(pb->entries[i]);
	  else return NULL;
        }
}
