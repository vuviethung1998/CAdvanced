#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "getFile.h"

void importCityList(char *fn, City *ct, MetroLine *ml){
	FILE *f;
	if((f= fopen(fn, "rb")) == NULL){
		printf("Cannot open %s\n", fn );
		return;
	}

	char c1[50], c2[50];
	fscanf(f,"%[^\n]", c1);
	for(int i = 0; i < 9; i++) {
		fscanf(f,"%[^\t]\t%[^\n]\n", ct[i].sign, ct[i].city);
		ct[i].num = i;
	}
	fscanf(f,"%[^\n]", c2);
	for(int i = 0; i < 5; i++) {
		fscanf(f,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", ml[i].ct[0].sign,ml[i].ct[1].sign,ml[i].ct[2].sign,ml[i].ct[3].sign,ml[i].ct[4].sign);
	}
	fclose(f);
}


ArrStruct cvToInt(City *ct, MetroLine *ml) {
	ArrStruct var;

	for(int i = 0; i <5; i ++ ) {
		 for(int j = 0; j <5 ; j ++) {
		 	for ( int k = 0; k < 9; k++) {
		 		if(strcmp(ml[i].ct[j].sign, ct[k].sign) == 0){
		 			var.Arr[i][j] = ct[k].num;
		 		}
		 	}
		 }
	}

	return var;
}

City nameToCity(char *name, City *ct, int num){
	for(int i = 0; i < num; i++ ){
		if(strcmp(name, ct[i].city) == 0)
			return ct[i];
	}
}


City intToCity(int num, City *ct, int noCt) {
	for(int i =0; i < noCt; i++) {
		if(num == ct[i].num)
			return ct[i];
	}
}