#include <stdio.h>
#include <stdlib.h> 
#include "graph.h"

Graph createGraph(int sizemax) {
	Graph g;
	g.sizemax = sizemax;
	g.matrix = (int *)calloc(sizemax*sizemax, sizeof(int));

	/*for(int i = 0; i< sizemax; i ++)  
		for(int j = 0; j < sizemax; j++)
			g.matrix[sizemax * i + j] = 0;
	*/
	return g;
}

void addEdge(Graph g, int v1, int v2) {
	g.matrix[v1*g.sizemax + v2] = 1;
	g.matrix[v2*g.sizemax + v1] = 1;
}

int adjacent(Graph g, int v1, int v2) {
	return g.matrix[v1 *g.sizemax + v2];
}

int getAdjacentVertices(Graph g, int v, int *output) {
	int total = 0;

	for(int i =0; i < g.sizemax; i++)
		if(adjacent(g, v, i))
			output[total++] = i;
	return total;
}

void dropGraph(Graph g) {
	free(g.matrix);
	g.matrix = NULL;
	g.sizemax = 0;
}