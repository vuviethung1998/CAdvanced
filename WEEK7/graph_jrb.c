#include <stdio.h>
#include <stdlib.h> 
#include "graph_jrb.h"

Graph createGraph(){
	Graph g = make_jrb();
	return g;
}
void addEdge(Graph graph, int v1, int v2){
	JRB node = jrb_find_int(graph,v1);	
	JRB tree;

	if(node == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph, v1, new_jval_v(tree));
	}else{
		tree = (JRB)jval_v(node->val);
	}
	jrb_insert_int(tree, v2, new_jval_i(1));

	node = jrb_find_int(graph,v2);
	if(node == NULL) {
		tree = make_jrb();
		jrb_insert_int(graph,v2, new_jval_v(tree));
	}else{
		tree = (JRB) jval_v(node->val);
	}

	jrb_insert_int(tree, v1,new_jval_i(1));
}

int adjacent(Graph graph, int v1, int v2){
	JRB node = jrb_find_int(graph, v1);
	if( node == NULL) return 0;
	else {
		if(jrb_find_int((JRB)jval_v(node->val), v2) == NULL)
			return 0;
		else return 1;
	}
}

int getAdjacentVertices (Graph graph, int v, int* output){
	JRB node = jrb_find_int(graph, v);
	JRB tree;
	int count = 0;

	if(node != NULL) {
		tree = (JRB)jval_v(node->val);
		count = 0;
		jrb_traverse(node ,tree)
			output[count ++] = jval_i(node->key);
	}

	return count;
}
void dropGraph(Graph graph){
	JRB node;
	jrb_traverse(node,graph)
		jrb_free_tree((JRB)jval_v(node->val));

	jrb_free_tree(graph);
}

void BFS(Graph graph, int start, int stop, void(*func)(int)) {
	JRB visited;
	Dllist node ,stack;
	int n, output[100], i,u,v;

	//Initialize the queue
	stack = new_dllist();
	dll_append(stack, new_jval_i(start));
	visited = make_jrb();

	while( !dll_empty(stack)) {
		node = dll_first(stack);
		u = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, u) == NULL) {//not yet visited
			//visit this vertex
			func(u);
			jrb_insert_int(visited, u, new_jval_i(1));
			//stop if visit the destination
			if(u == stop) break;
			//add unvisited neighbour to the queue
			n = getAdjacentVertices(graph, u, output);
			for(i = 0; i < n; i++) {
				v = output[i];
				if(jrb_find_int(visited ,v) == NULL) {
					dll_prepend(stack, new_jval_i(v));
				}
			}
		}
	}
	jrb_free_tree(visited);
}

void DFS(Graph graph, int start, int stop, void(*func)(int)) {
	JRB visited;
	Dllist node ,queue;
	int n, output[100], i,u,v;

	//Initialize the queue
	queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	visited = make_jrb();

	while( !dll_empty(queue)) {
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, u) == NULL) {//not yet visited
			//visit this vertex
			func(u);
			jrb_insert_int(visited, u, new_jval_i(1));
			//stop if visit the destination
			if(u == stop) break;
			//add unvisited neighbour to the queue
			n = getAdjacentVertices(graph, u, output);
			for(i = 0; i < n; i++) {
				v = output[i];
				if(jrb_find_int(visited ,v) == NULL) {
					dll_append(queue, new_jval_i(v));
				}
			}
		}
	}
	jrb_free_tree(visited);
}