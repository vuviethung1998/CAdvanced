#ifndef _DGRAPH_H_
#define _DGRAPH_H_

#include "libfdr/jval.h"
#include "libfdr/jrb.h"

typedef struct {
	JRB vertices;
	JRB edges;
} Graph;

Graph createGraph();

void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);

void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));

int DAG(Graph graph);
int topologicalSort(Graph graph, int *output);

void dropGraph(Graph graph);

#endif