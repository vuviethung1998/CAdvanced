#include <stdlib.h>
#include <stdio.h>
#include "dgraph.h"

void printVertex(int v);

int main(){
	Graph g = createGraph();

	addVertex(g, 0, "v0");
	addVertex(g, 1, "v1");
	addVertex(g, 2, "v2");
	addVertex(g, 3, "v3");

	addEdge(g, 1, 2);
	addEdge(g, 2, 0);
	addEdge(g, 1, 0);
	addEdge(g, 0, 3);

	printf("BFS: ");
	BFS(g, 1, -1, printVertex);
	printf("\n");

	printf("DFS: ");
	DFS(g, 1, -1, printVertex);
	printf("\n");

	if(DAG(g)) printf("The graph is a cycle\n");
	else printf("Have cycle in the graph\n");

	int output[10];

	int c = topologicalSort(g, output);
	printf("topologicalSort: ");
	for(int i = 0; i<c; i++)
		printf("%-4d", output[i]);
	printf("\n");

	

	return 0;
}

void printVertex(int v){
	printf("%-4d", v);
}