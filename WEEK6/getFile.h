#ifndef _GET_FILE_H_
#define _GET_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	char city[20];
	char sign[2];
	int num;
}City;

typedef struct {
	City ct[5];
}MetroLine;

typedef struct  {
	int Arr[5][5];
}ArrStruct;

void importCityList(char *fn, City *ct, MetroLine *ml);
ArrStruct cvToInt(City *ct, MetroLine *ml);
City nameToCity(char *name, City *ct, int num);
City intToCity(int num, City *ct, int noCt);

#endif