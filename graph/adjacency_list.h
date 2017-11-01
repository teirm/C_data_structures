/*
 * Purpose: Basic functions required
 *          for graph data structures
 * Author: Cyrusr
 * Date: 15 October 2017
 */

#include <stdlib.h>
#include "../linked_list/linked_list.h" /* These need to be moved */

typedef struct graph_node {
    unsigned long       index;
    void                *graph_info;
} graph_node;

typedef struct adjacency_list {
    unsigned long       vertices; 
    struct node       **list_array;         /* this is an array of lists */
} adjacency_list;

int node_comp(graph_node *a, graph_node *b);
unsigned long graph_first(adjacency_list *a_list, graph_node *v);
unsigned long graph_next(adjacency_list *a_list, graph_node *v, unsigned long req);
graph_node *vertex(adjacency_list *a_list, graph_node *v, unsigned long req);
int add_node(unsigned long start_vertex, unsigned long end_vertex, void *graph_info, adjacency_list *a_list);
