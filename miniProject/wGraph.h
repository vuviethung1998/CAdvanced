#ifndef __WGRAPH_H_
#define __WGRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXV 1000 //Max vertices

//su dung adjacency list 
//use linked list to store neighbor adjacent to each vertex
//for each graph keep counting from 1-> nvertices to assign to each vertex
/*
1 -2- 5
2-1-5-3-4
3-2-4
4-2-5-3
5-4-1-2
*/

//we save eaxh pair of edge in list n call it edge node
typedef struct edgenode{
    int y; //adjacency info: luu index cua canh 2
    double w; //edge weight VD: w = 10
    struct edgenode *next; //next edge in list     
}edgenode;//luu du lieu cua mot canh

typedef struct {
    edgenode *edges[MAXV +1];//list of edge nodes
    int degree[MAXV + 1]; //outdegree of each vertex
    char *vertex_names[MAXV + 1];
    int nvertices; //number of vertices in graph
    int nedges; //number of edges in graph
    bool directed;// graph directed?
} graph;

//BASIC OPERATION
void initgraph(graph *g, bool directed) {
    int i;

    g->nvertices = 0; //number of vertix = 0
    g->nedges = 0; //number of edges = 0
    g->directed = directed;// co huog

    for(i = 0; i <= MAXV; i++) {
        g->degree[i] = 0;//gan tung node co so luong outdegee = 0
        g->edges[i] = NULL;//tung cap canh  = NULL
        g->vertex_names[i] = NULL;
    }
}

/*
    - bieu dien mot cap canh co huong (x,y) = 1 edgenode y trong ajacency list cua x
    - degree dem so luong cap canh xuat phat tu  vertex x
    - trong undirected graph (x,y) xuat hien 2 lan
*/


/*
    The critical routine is insert edge. The new edgenode is inserted at the begin-
ning of the appropriate adjacency list, since order doesn’t matter. We parameterize
our insertion with the directed Boolean flag, to identify whether we need to insert
two copies of each edge or only one.
*/

//INSERT EDGE
void insertEdge (graph *g, int x, int y, double weight,bool directed){
    edgenode *p;
    p = (edgenode *)malloc(sizeof(edgenode));//allocate edge node storage
    p->w = weight;
    p->y = y;//index of outdegree node
    p->next = g->edges[x];
    g->edges[x] = p; // insert p at head of list

    /*
        VD: x = 1
            1: 2-3-5 => 1: p-2-3-5
    */
    g->degree[x] ++;//move to next index

    if(directed == false) {
        insertEdge(g,y,x, weight,true);
    }else {
        g->nedges ++;
    }
}

void insert_weighted_edge(graph *g, int x, int y, double weight, bool directed) {
  edgenode *p = (edgenode *)malloc(sizeof(edgenode)); // temp pointer

  p->w = weight;
  p->y = y;
  p->next = g->edges[x];

  g->edges[x] = p;
  g->degree[x]++;

  if (directed == false) {
    insert_weighted_edge(g, y, x, weight, true);
  } else {
    g->nedges++;
  }

  return;
}

//INSERT EDGE END
//END BASIC OPERATION

//VERTEX
void addVertexName(graph *g, int vertexIndex, char *name) {
    g->vertex_names[vertexIndex] = name;
    return;
}

char *getVertexName(graph *g, int vertexIndex){
  return g->vertex_names[vertexIndex];
}

//END VERTEX

//PRINT GRAPH
void printgraph(graph *g){
    int i;
    edgenode *p;

    for(i =1; i <= g->nvertices; i++) {
        printf("%d ", i);
        p = g->edges[i];
        while(p!= NULL ) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}

void printGraphByVertexIndex(graph *g){
  edgenode *p; // temp pointer

  for (int i = 1; i <= g->nvertices; i++)
  {
    printf("%d ", i);

    p = g->edges[i];
    while (p != NULL)
    {
      printf("--> %d", p->y);
      p = p->next;
    }
    printf("\n");
  }
  return;
}

void printGraphByVertexName(graph *g){
  edgenode *p; // temp pointer

  for (int i = 1; i <= g->nvertices; i++)
  {
    printf("%s ", getVertexName(g, i));

    p = g->edges[i];
    while (p != NULL)
    {
      printf("--> %s", getVertexName(g, p->y));
      p = p->next;
    }
    printf("\n");
  }
  return;
}

//END PRINT

//BUBBLE SORT
#ifndef __BUBBLE_SORT_LINKED_LIST_H__
#define __BUBBLE_SORT_LINKED_LIST_H__

void swap_y(edgenode *a, edgenode *b)
{
  int temp;
  temp = a->y;
  a->y = b->y;
  b->y = temp;

  temp = a->w;
  a->w = b->w;
  b->w = temp;
  return;
}

void bubble_sort_linked_list(edgenode*start)
{
  int swapped, i;
  edgenode *ptr1;
  edgenode *lptr = NULL;

  if (start == NULL)
    return;

  do
  {
    swapped = 0;
    ptr1 = start;

    while (ptr1->next != lptr)
    {
      if (ptr1->y > ptr1->next->y)
      {
        swap_y(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

#endif

void sort_vertex_graph(graph *g)
{
  for (int i = 0; i < g->nvertices; i++)
  {
    bubble_sort_linked_list(g->edges[i]);
  }
  return;
}

//EDGE
int hasEdge(graph *g, int id1, int id2) {
    int i;
    edgenode *p;
    p  = g->edges[id1];
    while(p!= NULL ) {
        if(p->y == id2){
            return 1;
        }
        p = p->next;
    }
    return 0;
}

double getWeight(graph *g, int id1, int id2) {
    int i;
    edgenode *p;

    if( (id1 >= 0) && (id1 < g->nvertices)) {
        if(hasEdge(g, id1, id2)) {
            return g->edges[id1][id2].w;
        }
        else {
            return 0;
        }
    }else {
        return 0;    
    }
}

//END EDGE

//DEGREE
int degree(graph *g, int id, bool directed) {
    int j;
    j= g->degree[id];

    return j;
}

int outdegree(graph *g, int id, bool directed){
    int j = 0;//outdegree

    edgenode *p;
    p = g->edges[id];
    while(p != NULL) {
        p = p->next;
        j++;
    }
    return j;
}

int indegree(graph *g, int id, bool directed){
    int i, j = 0;

    edgenode *p;
    for(i = 0; i < g->nvertices; i ++ ) {
        p = g->edges[i];

        while(p != NULL) {
            if(p->y == id) {
                j++;
                p = p->next;
            }
        }
    }
    return j;
}

//END DEGREE

//  DROP GRAPH
void dropgraph(graph *g){
    int i;
    edgenode *p;
    for(i = 0; i < g->nvertices; i++) {
        p=g->edges[i];

        while(p != NULL) {
            free(p);
            p = p->next;
        }
    }

    free(g);
}
//END DROP GRAPH


#ifndef __DECLARATION_DFS_BFS_H__
#define __DECLARATION_DFS_BFS_H__

bool processed[MAXV + 1];  // which vertex have been processed
bool discovered[MAXV + 1]; // which vertex have been discoverded
int parent[MAXV + 1];

#endif

#endif