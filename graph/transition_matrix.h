/*
 * Purpose: Basic functions required
 *          for graph data structures
 * Author: Cyrusr
 * Date: 15 October 2017
 */

#include <stdlib.h>
#include "ds_graph.h"

typedef struct transition_matrix {
    unsigned long       vertices;       
    int                 **cost_matrix; 
    graph_node          ***matrix;
} t_matrix;

unsigned long
graph_trans_matrix_first(
    t_matrix *t_mat,
    graph_node *v);

unsigned long
graph_trans_matrix_next(
    t_matrix *t_mat,
    graph_node *v,
    unsigned long req_index);

graph_node *
graph_trans_matrix_vertex(
    t_matrix *t_mat,
    graph_node *v,
    unsigned long req_index);
