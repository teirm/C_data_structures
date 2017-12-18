/*
 * Purpose: Basic functions required
 *          for graph data structures
 * Author:  Cyrus Ramavarapu
 * Date:    15 October 2017
 */

#include <stdlib.h>
#include "../linked_list/linked_list.h" /* These need to be moved */
#include "ds_graph.h"

typedef struct adjacency_list {
    unsigned long       vertices; 
    int               **cost_matrix;        /* this is an array of costs */ 
    struct node       **list_array;         /* this is an array of lists */
} adjacency_list;

/* graph_adj_list_node_comp
 *
 * comparator function for graph nodes
 * based on index
 *
 * @param a     - first graph node
 * @param b     - second graph node
 *
 * @return int  - 0, -1, or 1 if a > b, 
 *                a < b or a == b, respectively
 */
int
graph_adj_list_node_comp(
    graph_node *a,
    graph_node *b);

/* graph_adj_list_first
 *
 * return the lowest indexed member of vertex v's 
 * neighborhood
 *
 * @param a_list  - pointer to adjacency list structure
 * @param v       - pointer to vertex
 *
 * @return unsigned long - index of first node in neighbor
 *                         hood.
 */
unsigned long
graph_adj_list_first(
    adjacency_list *a_list,
    graph_node *v);

/*
 * graph_adj_list_next
 * 
 * return the vertex index of the one after requested
 * index
 *
 * @param a_list   - pointer to adjacency list structure
 * @param v        - graph node for which to search 
 *                   neighborhood.
 * @param req_index - first index less than one to return 
 * 
 * @ return unsigned long - index of first node with a higher 
 *                          index than req index
 *
 * Note: This assumes that the neighborhood is in 
 *       sorted order.  Sorting a linked list has not been
 *       done yet.
 */
unsigned long
graph_adj_list_next(
    adjacency_list *a_list,
    graph_node *v,
    unsigned long req);

/* graph_adj_list_vertex
 *
 * return the graph node at vertex i from
 * neighboorhood of v.
 * @param a_list   - pointer to adjacency list structure
 * @param v        - graph node for which to search 
 *                   neighborhood.
 * @param req_index - first index less than one to return
 *
 * @return graph_node * - pointer to graph node at req_index
 */
graph_node *
graph_adj_list_vertex(
    adjacency_list *a_list,
    graph_node *v,
    unsigned long req);

/* graph_adj_list_add_node
 * 
 * add a new node to the neighbohood of the start
 * vertex.
 *
 * @param start_vertex      - position of start vertex
 * @param end_vertex        - where the edge leads to
 * @param graph_info        - information that may need
 *                            to be held by graph
 * @param a_list            - pointer to adjacency list
 *                            structure
 *
 * @return int              - 0 on success.  
 */
int
graph_adj_list_add_node(
    unsigned long start_vertex,
    unsigned long end_vertex,
    void *graph_info,
    adjacency_list *a_list);

/* graph_adj_list_create_gnode
 *
 * create a graph node
 *
 * @param index         - index to give the new node
 * @param graph_info    - application specific information
 *                        for node to hold.
 */
graph_node *
graph_adj_list_create_gnode(
    unsigned long   index,
    void            *graph_info);
