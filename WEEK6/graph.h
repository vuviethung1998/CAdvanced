//ADT for graph

#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct 
{
	int *matrix;
	int sizemax;
}Graph;

Graph createGraph(int sizemax);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int* output); //return the number of adjacent vertices.
void dropGraph(Graph graph);

#endif