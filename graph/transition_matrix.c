/* Purpose: Implementation of graph functions
 *          using a transition matrix.
 * Author:  Cyrus
 * Date:    15 October 2017
 */

#include <ds/debug.h>

#include "transition_matrix.h" 

/* graph_trans_matrix_first
 *
 * Returns the first index in the neighborhood of
 * vertex v.
 *
 * @param t_mat             - pointer to transition matrix 
 *                            struct
 * @param v                 - vertex to search neighborhood
 *
 * @return unsigned long    - index of first node in neighbor
 *                            hood of v
 */
unsigned long
graph_trans_matrix_first (
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

/* graph_trans_matrix_next
 *
 * Return the index after requested index
 * in neighborhood of v
 *
 * @param   t_mat           - pointer to transitiom matrix
 *                            structure
 * @param   v               - vertex to search neighborhood of
 * @param   req_index       - index requested.
 *
 * @return unsigned long    - index in neighborhood after requested
 *                            or -1 if does not exist.
 */
unsigned long
graph_trans_matrix_next (
    t_matrix        *t_mat,
    graph_node      *v,
    unsigned long   req_index)
{
    unsigned long   i;
    unsigned long   next_node_index = -1;
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

/* graph_trans_matrix_vertex
 *  
 * Return the graph node indexed at req_index
 * in neighborhood of v if it exists.
 *
 * @param   t_mat           - pointer to transitiom matrix
 *                            structure
 * @param   v               - vertex to search neighborhood of
 * @param   req_index       - index requested.
 *
 * @return  graph_node *    - pointer to graph node at req_index in
 *                            neighboord of v if it exists.  Otherwise
 *                            NULL.
 */
graph_node *
graph_trans_matrix_vertex (
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
