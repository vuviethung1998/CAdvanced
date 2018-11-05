#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "dgraph.h"
//////////////////////////////////////////////////////////////////////

#define enqueue(queue, id) dll_append(queue, new_jval_i(id))
#define push(stack, id) dll_prepend(stack, new_jval_i(id))
#define pop(stack) dequeue(stack)


Graph createGraph()
{
     Graph g;
     g.edges = make_jrb();
     g.vertices = make_jrb();
     return g;
}


/* insert an edge to directed graph*/
void insertEdge(Graph g, int v1, int v2, double w)
{
     JRB edges = g.edges;
     JRB adj_list = make_jrb();
     Jval data;

     if(w < 0)
          printf("WARNING: weight < 0\n");

     /* find if v1 is alreadly in jrb */
     JRB found = jrb_find_int(edges, v1);

     if(found == NULL){
          /* if v1 is not in graph */
          /* create node v1: key is v1, data is adjacent list */

          /* create adj list of v1*/
          jrb_insert_int(adj_list, v2, jd(w));
          /* add adj_list to data */
          data = new_jval_v(adj_list);

          /* add node v1 to graph */
          jrb_insert_int(edges, v1, data);
     }else{
          /* if v1 is already in graph
          then determine if v2 is in adj_list of v1 */
          adj_list = (JRB) jval_v(found->val);
          found = jrb_find_int(adj_list, v2);

          if(found == NULL){
               // if not found v2
               // insert v2 into adjlist of v1
               jrb_insert_int(adj_list, v2, jd(w));
          }//end nested-if

     }// end else
} //end insertEdge


Jval jv(char *s)
{
     // init struct
     attrb a = (attrb) malloc(sizeof(attrb));
     if(s){
          char *sm = (char*) malloc(strlen(s));
          strcpy(sm, s);    
          a->name = sm;
     }else{
          a->name = NULL;
     }  
     a->ind = 0;
     a->d = DBL_MAX;
     Jval val = new_jval_v(a);
     return val;
}

attrb getattrb(JRB node)
{
     if(!node){
          printf("Node is null in function getattrb\n");
          exit(1);
     }
     return ((attrb) jval_v(node->val));
}

/* insert new node to graph, if the node is already exist,
change its data
This function should use a function pointer to initialize vertices */
void addVertex(Graph g, int id, char *name)
{
     JRB vertices = g.vertices;
     JRB found;

     // check if node id is in graph
     found = jrb_find_int(vertices, id);

     if(found == NULL){
          // if not found, insert vertex id to graph
          jrb_insert_int(vertices, id, jv(name));
     }else{
          // if found, change the data of node id
          if(!name){
               printf("WARNING: name is null\n");
               return;
          } 
          attrb a = getattrb(found);
          if(strcmp(a->name, name)){
               free(a->name);
               found->val = jv(name);
          }
     }

}


/* return the number of incoming edges,
return its incoming nodes at output */
int inDegree(Graph g, int id, int* output)
{
     JRB node;
     JRB found;
     int count = 0;

     jrb_traverse(node, g.edges){
          found = jrb_find_int((JRB) jval_v(node->val), id);
          if(found != NULL){
               output[count] = jval_i(node->key);
               count++;
          } // end if
     }// end traverse

     return count;
} //end inDegree


/* return the number of out going nodes
its out going nodes are returned at output */
int outDegree(Graph g, int id, int* output)
{
     JRB found;
     JRB tmp;
     JRB edges = g.edges;
     JRB adjlist;
     int count = 0;

     found = jrb_find_int(edges, id);

     if(found != NULL){
          adjlist = (JRB)jval_v(found->val);
          jrb_traverse(tmp, adjlist){
               output[count] = jval_i(tmp->key);
               count++;
          } // end traverse
     } // end if

     return count;
} // end outDegree


/* return the name of a vertex */
char *getVertex(Graph g, int id)
{
     JRB found;
     JRB vertices = g.vertices;

     found = jrb_find_int(vertices, id);

     if(found != NULL){
          attrb a = getattrb(found);
          return a->name;
     }else{
          return NULL;
     }
}

/* deallocate memory and remove graph */
void dropGraph(Graph g)
{
     JRB vertices = g.vertices;
     JRB tmp;
     attrb a;

     jrb_traverse(tmp, vertices){
          a = getattrb(tmp);
          free(a->name);
          free(a);
     }
}


/*
void addNode(Graph  g, int v1, int v2, char* name1, char* name2)
{
     insertEdge(g, v1, v2);
     addVertex(g, v1, name1);
     addVertex(g, v2, name2);
}
*/


int hasEdge(Graph g, int v1, int v2)
{
     JRB edges = g.edges;
     JRB adjlist;
     JRB found;

     found = jrb_find_int(edges, v1);
     if(found){
          adjlist = (JRB) jval_v(found->val);
          found = jrb_find_int(adjlist, v2);
          if(found)
               return 1;
          else return 0;
     }else
          return 0;
}


int dequeue(Dllist queue)
{
     Dllist first = dll_first(queue);
     int v = jval_i(first->val);
     dll_delete_node(first);
     return v;
}


void tsort(Graph g)
{
     Dllist queue = new_dllist();
     JRB edges = g.edges;
     JRB vertices = g.vertices;
     JRB tmp;
     int output[100];
     int num;
     int i;
     int ind;
     int id;
     attrb a;

     jrb_rtraverse(tmp, vertices){
          id = jval_i(tmp->key);
          a = getattrb(tmp);
          ind = inDegree(g, id, output);
          a->ind = ind;
          if(ind == 0){
               enqueue(queue, id);
          }
     }

     while(!dll_empty(queue)){
          id = dequeue(queue);
          printf("%s\n", getVertex(g, id));// thay bang function pointer
          num = outDegree(g, id, output);
          for(i = 0; i < num; i++){
               tmp = jrb_find_int(vertices, output[i]);
               a = getattrb(tmp);
               a->ind -= 1;
               if(a->ind == 0) enqueue(queue, output[i]);
          }
     }
}


JRB getAdjList(Graph g, int v)
{
     JRB found = jrb_find_int(g.edges, v);

     if(found){
          return (JRB) jval_v(found->val);
     }else
          return NULL;
}


double getWeight(Graph g, int v1, int v2)
{
     JRB found;
     JRB adjlist = getAdjList(g, v1);

     if(adjlist){
          found = jrb_find_int(adjlist, v2);
          if(found)
               return jval_d(found->val);
          else
               return DBL_MAX;
     }else{
          return DBL_MAX;
     }

}


/* return the node of g.vertices containing id
null if not found
*/
JRB getVertexNode(Graph g, int id)
{
     JRB vertices = g.vertices;
     JRB found = jrb_find_int(vertices, id);

     if(found){
          return found;
     }else{
          return NULL;
     }
}


/* init graph for djistra algorithm */
void initSingleSource(Graph g, int s)
{
     JRB vertices = g.vertices;
     JRB v;
     attrb a;

     jrb_traverse(v, vertices){
          a = getattrb(v);
          a->d = DBL_MAX;
          a->predecessor = NULL;
     }

     v = getVertexNode(g, s);
     if(v){
          a = getattrb(v);
          a->d = 0;
     }else{
          printf("ERROR: node %d does not exist\n", s);
          exit(1);
     }
}


void relax(Graph g, int u, int v)
{
     JRB node_u = getVertexNode(g, u);
     JRB node_v = getVertexNode(g, v);

     if(!node_u){
          printf("In relax function, node_u == NULL\n");
          exit(1);
     }

     if(!node_v){
          printf("In relax function, node_v == NULL\n");
          exit(1);
     }

     attrb attrb_u = getattrb(node_u);
     attrb attrb_v = getattrb(node_v);
     double w = getWeight(g, u, v);

     if(attrb_v->d > attrb_u->d + w){
          attrb_v->d = attrb_u->d + w;
          attrb_v->predecessor = node_u;
     }

}


int getAdjVertices(Graph g, int id, int* output)
{
     JRB tmp;
     int i=0;
     JRB adjlist = getAdjList(g, id);
     if(!adjlist){
          return -1;
     }
     jrb_traverse(tmp, adjlist){
          output[i] = jval_i(tmp->key);
          i++;
     }

     return i;
}


int extractMin(Graph g, Dllist Q)
{
     int min = INT_MAX;
     Dllist min_node;
     JRB v;
     int id;
     Dllist tmp;
     attrb a;

     dll_traverse(tmp, Q){
          v = getVertexNode(g, jval_i(tmp->val));
          a = getattrb(v);
          if(min > a->d){
               min = a->d;
               min_node = tmp;
          }
     }

     id = jval_i(min_node->val);
     dll_delete_node(min_node);

     return id;
}


double shortestPath(Graph g, int s, int d, int *path, int *len)
{
     int i = 0;
     int j, pre;
     int u;
     int n;
     int adj_vertices[100];
     double w = 0;
     JRB tmp;
     Dllist Q = new_dllist();
     initSingleSource(g, s);
     // add vertices to queue
     jrb_traverse(tmp, g.vertices){
          dll_append(Q, tmp->key);
     }

     pre = s;

     while(!dll_empty(Q)){
          u = extractMin(g, Q);
          if(u != pre){
               w += getWeight(g, pre, u);
          }
          pre = u;

          path[i] = u;
          i++;
          if(u == d){
               // reach the destination
               *len = i;
               return w;
          }
          n = getAdjVertices(g, u, adj_vertices);
          for(j = 0; j < n; j++){
               relax(g, u, adj_vertices[j]);
          }
     }

     return DBL_MAX;
}


void BFS(Graph g, int s, int (*visit)(Graph, int))
{
     Dllist queue;
     JRB tmp;
     attrb a;
     int u, num_adj, i;
     int adj[1000];

     // mark all the vertices as unvisited
     jrb_traverse(tmp, g.vertices){
          a = getattrb(tmp);
          a->visited = 0;
     }

     // visit the first vertex
     visit(g, s);
     tmp = jrb_find_int(g.vertices, s);
     a = getattrb(tmp);
     a->visited = 1;

     // initialize the queue
     queue = new_dllist();
     dll_append(queue, ji(s));

     // BFS
     while(!dll_empty(queue)){
          /* pick up 1 vertex
          and get its adj vertices*/
          u = dequeue(queue);
          num_adj = getAdjVertices(g, u, adj);
          for(i = 0; i < num_adj; i++){
               tmp = jrb_find_int(g.vertices, adj[i]);
               a = getattrb(tmp);
               if(!(a->visited)){
                    visit(g, adj[i]);
                    a->visited = 1;
                    enqueue(queue, adj[i]);
               }
          }
     }

     // free the queue
     free_dllist(queue);
}



int visit(Graph g, int v)
{
     attrb a;
     JRB tmp;

     tmp = jrb_find_int(g.vertices, v);

     if(!tmp){
          printf("tmp is null in visitBFS function\n");
          exit(1);
     }

     a = getattrb(tmp);
     printf("%d: %s\n", jval_i(tmp->key), a->name);

     return 0;
}


/* depth first search */
void DFS(Graph g, int s, int (*visit)(Graph, int))
{
     Dllist stack;
     JRB tmp;
     attrb a;
     int u, num_adj, i;
     int adj[1000];

     // mark all the vertices as unvisited
     jrb_traverse(tmp, g.vertices){
          a = getattrb(tmp);
          a->visited = 0;
     }

     // visit the first vertex
     /*visit(g, s);
     tmp = jrb_find_int(g.vertices, s);
     a = getattrb(tmp);
     a->visited = 1;
     */

     // initialize the stack
     stack = new_dllist();
     push(stack, s);

     // BFS
     while(!dll_empty(stack)){
          /* pick up 1 vertex
          and get its adj vertices*/
          u = pop(stack);
          // visit this node
          tmp = jrb_find_int(g.vertices, u);
          a = getattrb(tmp);
          if(!a->visited){
               visit(g, u);
               a->visited = 1;
          }
          

          // discover unvisited adj nodes
          // and push it into the stack
          num_adj = getAdjVertices(g, u, adj);
          //printf("%d: %d\n", u, num_adj);
          //for(i = num_adj-1; i >= 0 ; i--){
          for(i = 0; i < num_adj ; i++){
               tmp = jrb_find_int(g.vertices, adj[i]);
               a = getattrb(tmp);
               if(!(a->visited)){
                    push(stack, adj[i]);
               }// end if
          } // end for
     } // end while

     free_dllist(stack);
}

//addon function 
//quanghien95
int dll_find(Dllist l, int key)
{
     Dllist temp;
     dll_traverse(temp, l)
     {
          if (key == jval_i(temp->val))
               return 1;
     }
     return 0;
}
int DAG(Graph G)
{
     Dllist arbitraryVertice = new_dllist();

     JRB node;
     jrb_traverse(node, G.vertices)
     {
          dll_append(arbitraryVertice, (node->key));
     }

     while (!dll_empty(arbitraryVertice))
     {
          Dllist l = new_dllist();
          int source = jval_i(dll_first(arbitraryVertice)->val);
          dll_append(l, new_jval_i(source));
          dll_delete_node(dll_first(arbitraryVertice));
          
          Dllist visited = new_dllist();
          while (!dll_empty(l))
          {
               int u = jval_i(dll_last(l)->val);
               dll_delete_node(dll_last(l));

               if (!dll_find(visited, u))
               {
                    dll_append(visited, new_jval_i(u));
                    
                    int output[ARRSIZE];
                    int n = outDegree(G, u, output);
                    if (n != 0)
                    {
                         int i;
                         for (i = n-1; i >= 0; i--) 
                         {
                              if (!dll_find(visited, output[i]))
                              {
                                   dll_append(l, new_jval_i(output[i]));
                              }
                              else if (output[i] == source)
                              {
                                   free_dllist(visited);
                                   free_dllist(l);
                                   free_dllist(arbitraryVertice);
                                   return 1;
                              }
                         }
                    }
               }
          }
     }

     free_dllist(arbitraryVertice);
     return 0;
}

int Visit(Graph G, int v)
{
     JRB node;
     node = jrb_find_int(G.vertices, v);
     printf("%s ", jval_s(node->val));
     return 0;
}

void TopologicalSort(Graph G)
{
     if (DAG(G))
     {
          printf("Can not make topological sort\n"); 
          return; 
     }

     Dllist tpQueue = new_dllist();
     JRB indegree = make_jrb();
     JRB node;

     jrb_traverse(node, G.vertices)
     {
          int iv = inDegree(G, jval_i(node->key), NULL);
          jrb_insert_int(indegree, jval_i(node->key), new_jval_i(iv));
          if (iv == 0)
               dll_append(tpQueue, node->key);
     }
     
     while (!dll_empty(tpQueue))
     {
          Visit(G, jval_i(dll_first(tpQueue)->val));

          int arc[ARRSIZE]; 
          int sizeofArc = outDegree(G, jval_i(dll_first(tpQueue)->val), arc);

          dll_delete_node(dll_first(tpQueue));
          
          int i;
          for(i = 0; i < sizeofArc; i++)
          {
               JRB tmp;
               tmp = jrb_find_int(indegree, arc[i]);

               if (tmp != NULL)
               {
                    tmp->val = new_jval_i(jval_i(tmp->val)-1);
                    if (jval_i(tmp->val) <= 0)
                         dll_append(tpQueue, tmp->key);
               }    
          }
     }

     jrb_free_tree(indegree);
}
///////////////////////////////