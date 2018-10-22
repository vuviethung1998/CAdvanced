#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "jval.h"
#include "phonebook_jrb.h"

void insertNode(JRB tree, char *key, Jval val){
	JRB node = jrb_find_str(tree,key);

	if(node == NULL)
		jrb_insert_str(tree, strdup(key), val);
	else
		node->val = val;
}

void searchPhone(JRB tree, char *key){
	JRB node = jrb_find_str(tree, key);
	if(node == NULL)
    	printf("Entry doesn't exist\n");
 	else
    	printf("\n%s: %ld\n\n", jval_s(node->key), jval_l(node->val));
    return;
}

void jrb_print_file(char *fn, JRB tree)
{
	FILE *f;
	if ((f = fopen(fn, "w+b")) == NULL) {
    	printf("Cannot open %s\n", fn);
    	return;
 	}

  JRB temp;
  for (temp = jrb_first(tree);temp != jrb_nil(tree); temp = jrb_next(temp))
    	fprintf(f, "%s\t%ld\n", jval_s(temp->key) ,jval_l(temp->val));
    
  fclose(f);
}
void deleteEntry(char *fn,char *key, JRB tree) {
	JRB temp;
	for (temp = jrb_first(tree);temp != jrb_nil(tree); temp = jrb_next(temp))
		if(strcmp(key, jval_s(temp->key)) == 0 )
			jrb_delete_node(temp);
	return;
}

void dropPhoneBook(JRB tree) {
	JRB temp;

	jrb_traverse(temp, tree){
		free(jval_s(temp->key));
		free(jval_l(temp->val));
	}

	jrb_free_tree(tree);
}