/* Purpose: Implementation of graph
 *          functions using the 
 *          adjacency list.
 * Author:  cyrus
 * Date:    15 October 2017
 */

#include  "adjacency_list.h"


int
node_comp(
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

    
graph_node *
create_graph_node(
    unsigned long   index,
    void            *graph_info)
{
    struct graph_node   *ret_graph_node;

    ret_graph_node = calloc(1, sizeof *ret_graph_node);
    
    ret_graph_node->index = index;
    ret_graph_node->graph_info = graph_info;

    return ret_graph_node;
}

int
add_node(
    unsigned long start_vertex,
    unsigned long end_vertex,
    void          *graph_info,
    adjacency_list  *a_list)
{
    int rc = 0;
    int length = 0;
    

    graph_node *new_graph_node = 
        create_graph_node(end_vertex, graph_info);
    if (new_graph_node == NULL) {
        return 1;
    }
    
    struct node *new_list_node = 
        calloc(1, sizeof *new_list_node);
    if (new_list_node == NULL) {
        return 1;
    }
    
    new_list_node->value =
        new_graph_node;

    length = list_get_len(a_list->list_array[start_vertex]);  
    rc = list_insert(new_list_node,
                     length+1,
                     &a_list->list_array[start_vertex]);
    return rc;
}

unsigned long
graph_first(
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

unsigned long
graph_next(
    adjacency_list      *a_list,
    graph_node          *v,
    unsigned long       req)
{
    struct node         *vertex_node = NULL;
    struct node         *previous_node = NULL;
    struct node         *return_node = NULL;

    vertex_node = a_list->list_array[v->index];

    if (!vertex_node) {
        return 0;
    }
    
    previous_node = list_retrieve(req, &vertex_node);
    
    if (!previous_node) {
        return 0;
    }

    return_node = previous_node->next;
    
    if (!return_node) {
        return 0;
    }
    
    return ((graph_node*)return_node)->index;
}

graph_node *
vertex(
    adjacency_list      *a_list,
    graph_node          *v,
    unsigned long       req)
{
    struct node         *vertex_node = NULL;
    struct node         *return_node = NULL;

    vertex_node = a_list->list_array[v->index];

    if (!vertex_node) {
        return NULL;
    }

    return_node = list_retrieve(req, &vertex_node);
    
    if (!return_node) {
        return NULL;
    }

    return ((graph_node *)return_node->value);
}









