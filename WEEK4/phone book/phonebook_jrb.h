#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"

void insertNode(JRB tree, char *key, Jval val);
void searchPhone(JRB tree, char *key);
void jrb_print_file(char *fn, JRB t);
void deleteEntry(char *fn,char *key, JRB tree);
void dropPhoneBook(JRB tree);