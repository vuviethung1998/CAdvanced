#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define DBL_MAX LONG_MAX
#define ji(i) new_jval_i(i) // make new jval of int
#define jd(d) new_jval_d(d) // make new jval of double

typedef struct{
     char *name;
     int ind;
     int visited;
     double d;
     JRB predecessor;
} at;

typedef at* attrb;


typedef struct{
     JRB edges;
     JRB vertices;
} Graph;

/*
The structure of this graph is as follows:
Edges of the graph is a JRB tree with the key of each node is a vertex.
Its adjacent verteces are stored in a jval which is a pointer to another JRB tree.
This nested tree holds the adj vertices in the key of each node,
and the weight in the data or val of each node
Vertices of the graph is a JRB tree with the key is the id of the node.
This id is identical to the id in the edges tree.
The val of each node is a struct that hold all the necessary information about
each vertices.
*/

//addon by quanghien95
#define ARRSIZE 1000
int DAG(Graph G);
void TopologicalSort(Graph G);
////////////////
Graph createGraph();
void addVertex(Graph, int, char *);
void insertEdge(Graph, int, int, double);
int inDegree(Graph, int, int*);
int outDegree(Graph, int, int*);
char *getVertex(Graph, int);
int hasEdge(Graph, int, int);
void dropGraph(Graph);
void tsort(Graph);       //TopologicalSort
attrb getattrb(JRB);
double getWeight(Graph, int, int);
double shortestPath(Graph, int, int, int *path, int *len);
JRB getVertexNode(Graph, int);
JRB getAdjList(Graph , int);
/* return -1 if there is no adj vertices */
int getAdjVertices(Graph, int, int*);
/* breath first search
The number of adj vertices BFS can holds is 1000 max
so if it exceeds go to source code and change it */
void BFS(Graph g, int s, int (*visit)(Graph, int));
/* depth first search */
void DFS(Graph g, int s, int (*visit)(Graph, int));
//void addNode(Graph, int, int, char*, char*);
//int getComponents(Graph);


/* this function is used to visit nodes in BFS
you can define you own function and pass it to BFS */
int visit(Graph g, int v);

#endif