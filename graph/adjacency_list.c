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

unsigned long
graph_first(
    adjacency_list      *a_list,
    graph_node          *v)
{
    struct node         *vertex_node = NULL;
    graph_node          *return_node = NULL;

    vertex_node = list_retrieve(v->index, &a_list->list_head);
    
    if (!vertex) {
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

    vertex_node = list_retrieve(v->index, &a_list->list_head);
    
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

    vertex_node = list_retrieve(v->index, &a_list->list_head);

    if (!vertex_node) {
        return NULL;
    }

    return_node = list_retrieve(req, &vertex_node);
    
    if (!return_node) {
        return NULL;
    }

    return ((graph_node *)return_node->value);
}









