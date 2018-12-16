#ifndef __WEIGHTED_GRAPH_ALGO_H__
#define __WEIGHTED_GRAPH_ALGO_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./wGraph.h"

#define INT_MAX 100000000

/* Dijkstra's Algorithm------BEGIN----*/
/* for finding shortest path */
int parent_dijkstra[MAXV + 1];
bool intree_dijkstra[MAXV + 1]; /* is the vertex in tree yet ?*/
double distance_dijkstra[MAXV + 1];/* the distance vertex is from start */

void init_dijkstra(graph *g) {
  for (int i = 1; i <= g->nvertices; i++) {
    intree_dijkstra[i] = false;
    distance_dijkstra[i] = INT_MAX;
    parent_dijkstra[i] = -1;
  }
  return;
}

void dijkstra(graph *g, int start) {
  int i;
  edgenode *p;
  int v;                 /* curretn vertex to process */
  int w;                 /* candidate for next vertex in tree */
  double weight;            /* edge weight */
  double dist;              /* best current distance from start */

  init_dijkstra(g);

  distance_dijkstra[start] = 0;
  v = start;

  while (intree_dijkstra[v] == false) {
    intree_dijkstra[v] = true;
    p = g->edges[v];
    while (p != NULL) {
      w = p->y;
      weight = p->w;
      if (distance_dijkstra[w] > (distance_dijkstra[v] + weight)) {
        distance_dijkstra[w] = distance_dijkstra[v] + weight;
        parent_dijkstra[w] = v;
      }
      p = p->next;
    }

    v = 1;
    dist = INT_MAX;
    for (i = 1; i <= g->nvertices; i++) {
      if (intree_dijkstra[i] == false && dist > distance_dijkstra[i]) {
        dist = distance_dijkstra[i];
        v = i;
      }
    }

  }

  return ; 
}

// void find_path_dijkstra(graph *g, int start, int end) {
// 	if (start == end || end == -1) {
//     printf("\n%d", start);
// 	} else {
// 		find_path_dijkstra(g, start, parent_dijkstra[end]);		
//     printf(" %d", end);
// 	}
// 	return;
// }

int find_path_dijkstra(graph *g, int start, int end,int arr[]) {
  int i =0;
  while(1) {
    arr[i] =end;
    end = parent_dijkstra[end];
    i++;
    if(start ==end || end == -1) {
      arr[i] =start;
      break ;
    }
  }
  return i;
  // for(int j = i; j >= 0; j --) {
  //   printf("%d ", arr[j]);
  // }
}

// void find_path_dijkstra(graph *g, int start, int end,int arr[]) {
//   int i = 0;
//   while(start != end || end != -1) {
//     arr[i] =end;
//      printf(" %d", end);
//     end = parent_dijkstra[end];
//     i++;
//   }
//   arr[i] =start;
//   printf("\n%d", start);
// }
/* Dijkstra's Algorithm-------END------*/

#endif