#ifndef	_GRAPHJRB_H_
#define	_GRAPHJRB_H_

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, int v, int* output);
void printGraph();
void dropGraph(Graph graph);
void BFS(Graph graph, int start, int stop, void(*func)(int));
void DFS(Graph graph, int start, int stop, void(*func)(int));

#endif
