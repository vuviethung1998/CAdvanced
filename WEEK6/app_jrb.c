#include <stdio.h>
#include <stdlib.h>
#include "graph_jrb.h"
#include "getFile.h"
#define FN "demo.txt"

int main(){
	int i , n[9], output[9][100], outputCt[100];
	Graph g = createGraph(100);
	
	City ct[9];
	MetroLine ml[5];
	char name[20];

	importCityList(FN,ct, ml);
	ArrStruct var;
	var =  cvToInt(ct, ml);

	for(int i = 0;i < 5; i ++) {
		for(int j = 0; j < 5; j++) {
			printf("%d ", var.Arr[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i< 5; i++){
		for (int j = 0; j < 4; j++)
		{
			addEdge(g, var.Arr[i][j], var.Arr[i][j+1]);	
		}
	}
	
	for(int i = 0; i < 9; i++){
		n[i] = getAdjacentVertices(g,i,output[i]);

		if(n[i] == 0)
			printf("No adjacent vertices of node S%d\n", i+1);
		else{
			printf("Adjacent vertices of node S%d: \n", i +1);
			for (int j = 0; j < n[i]; j++){
				printf("%5d ", output[i][j]);
			}
			printf("\n");
		}	
		
	}

	printf("Input name of station:\n");
	gets(name);

	City Ct = nameToCity(name, ct, 9);
	int nCt = Ct.num;

	int n1 = getAdjacentVertices(g, nCt, outputCt);

	if(n1 == 0)
		printf("No adjacent cities of node S%s\n", name);
	else{
		printf("Adjacent vertices of city %s: \n", name);

		for(int i = 0;i < n1; i ++){
			City ctName = intToCity(outputCt[i], ct, nCt);
			printf("%5s ", ctName.city);
		}
	}
	printf("\n");
	dropGraph(g);
}