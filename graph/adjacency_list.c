/* Purpose: Implementation of graph
 *          functions using the 
 *          adjacency list.
 * Author:  cyrus
 * Date:    15 October 2017
 * Description:
 *
 * The adjacency list is organized as follows:
 * 
 *    V 
 *  -----
 * |  1  | -> 2 -> n 
 *  -----
 * |  2  | 
 *  -----
 *  . . .
 *  -----
 * |  n  | -> 2
 *  -----
 *
 *  The array of link lists V just holds link lists.
 *  To determine the neighborhod of Vertex m examine
 *  the link list V[m].
 */
#include <stdio.h>

#include <ds/debug.h>
#include  "adjacency_list.h"

#define ADJ_LIST_DEBUG 1

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
    graph_node      *a,
    graph_node      *b)
{
    if (a->index > b->index) {
        return 1;
    } else if (a->index < b->index) {
        return -1;
    } else {
        return 0;
    }
}


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
    void            *graph_info)
{
    struct graph_node   *ret_graph_node;

    ret_graph_node = calloc(1, sizeof *ret_graph_node);
   
    if (ret_graph_node == NULL) {
        return NULL;
    }

    ret_graph_node->index = index;
    ret_graph_node->graph_info = graph_info;

    return ret_graph_node;
}

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
    void          *graph_info,
    adjacency_list  *a_list)
{
    graph_node *new_graph_node = 
        graph_adj_list_create_gnode(end_vertex, graph_info);
    if (new_graph_node == NULL) {
        return DS_ENOMEM;
    }
#ifdef ADJ_LIST_DEBUG
    printf("[%s:%d] a_list->list_array[start_vertex]=%p\n",
            DEBUG_INFO, 
            a_list->list_array[start_vertex]);
#endif /* ADJ_LIST_DEBUG */


    struct node *new_list_node = 
        calloc(1, sizeof *new_list_node);
    if (new_list_node == NULL) {
        return DS_ENOMEM;
    }

    new_list_node->value =
        new_graph_node;

#ifdef ADJ_LIST_DEBUG
    printf("[%s:%d] start_vertex: %d end_vertex: %d \
            new_list_node->value: %p\n",
            DEBUG_INFO, start_vertex, end_vertex,
            new_list_node->value);
#endif /* ADJ_LIST_DEBUG */ 

    return list_append(new_list_node,
                     &(a_list->list_array[start_vertex]));
}

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
    adjacency_list      *a_list,
    graph_node          *v)
{
    struct node         *vertex_node = NULL;
    graph_node          *return_node = NULL;

    vertex_node = a_list->list_array[v->index];

    if (!vertex_node) {
        return 0;
    }

    if (!vertex_node->next) {
        return 0;
    }

    return_node = vertex_node->next->value;

    return return_node->index;
}

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
    adjacency_list      *a_list,
    graph_node          *v,
    unsigned long       req_index)
{
    struct node         *vertex_node = NULL;
    struct node         *previous_node = NULL;
    struct node         *return_node = NULL;

    vertex_node = a_list->list_array[v->index];

    if (!vertex_node) {
        return 0;
    }
  
    /* NOTE: requires that the nodes are in sorted order */
    previous_node = list_retrieve(req_index, &vertex_node);
    
    if (!previous_node) {
        return 0;
    }

    return_node = previous_node->next;
    
    if (!return_node) {
        return 0;
    }
    
    return ((graph_node*)return_node)->index;
}

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
    adjacency_list      *a_list,
    graph_node          *v,
    unsigned long       req_index)
{
    struct node         *vertex_node = NULL;
    struct node         *return_node = NULL;

    vertex_node = a_list->list_array[v->index];

    if (!vertex_node) {
        return NULL;
    }

    return_node = list_retrieve(req_index, &vertex_node);
    
    if (!return_node) {
        return NULL;
    }

    return ((graph_node *)return_node->value);
}
