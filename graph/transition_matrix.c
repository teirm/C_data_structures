/* Purpose: Implementation of graph functions
 *          using a transition matrix.
 * Author:  Cyrus
 * Date:    15 October 2017
 */

#include "transition_matrix.h" 

unsigned long
first (
    t_matrix        *t_mat,
    graph_node      *v)
{
    unsigned long i;  
    unsigned long first_node_index = 0; 
    unsigned long v_index = v->index;

    for (i = 0; i < t_mat->vertices; i++) {
        if (t_mat->matrix[v_index][i]) {
            first_node_index = 
                t_mat->matrix[v_index][i]->index;
            break;
        }
    }
    
    return first_node_index;
}

unsigned long
next (
    t_matrix        *t_mat,
    graph_node      *v,
    unsigned long   req_index)
{
    unsigned long   i;
    unsigned long   next_node_index = 0;
    unsigned long   v_index = v->index;

    for (i = 0; i < t_mat->vertices; i++) {
        if (t_mat->matrix[v_index][i]) {
            if (req_index == 0) {
                next_node_index = 
                    t_mat->matrix[v_index][i]->index;
                break;
            }
            req_index--;
        }
    }

    return next_node_index;
}

graph_node *
vertex (
    t_matrix            *t_mat,
    graph_node          *v,
    unsigned long       req_index)
{
    unsigned long       i;
    unsigned long       v_index = v->index;
    graph_node          *ret_node = NULL;

    for (i = 0; i < t_mat->vertices; i++) {
        if (t_mat->matrix[v_index][i]) {
            req_index--;
            if (req_index == 0) {
                ret_node = t_mat->matrix[v_index][i];
                break; 
            }
        }
    }

    return ret_node;
}


