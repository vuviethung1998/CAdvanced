#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i, n, output[100];

	Graph g = createGraph(100);
	addEdge(g, 0 ,1);
	addEdge(g, 0 ,2);
	addEdge(g, 1,2);
	addEdge(g, 1 , 3);
	n = getAdjacentVertices(g, 1, output);
	if(n == 0 )
		printf("NO adjacent vertices of node 1\n");
	else {
		printf("adjacent vertices of node 1:\n");
		for(i = 0;i <n; i ++)
			printf("%5d\n", output[i]);
	}
	printf("\n");
	dropGraph(g);
}