/*
 * Purpose: Basic functions required
 *          for graph data structures
 * Author: Cyrusr
 * Date: 15 October 2017
 */

#include <stdlib.h>


typedef struct graph_node {
    unsigned long       index;
    void                *graph_info;
} graph_node;


typedef struct transition_matrix {
    unsigned long       vertices;       
    graph_node          ***matrix;
} t_matrix;



unsigned long first(t_matrix *t_mat, graph_node *v);
unsigned long next(t_matrix *t_mat, graph_node *v, unsigned long req_index);
graph_node *vertex(t_matrix *t_mat, graph_node *v, unsigned long req_index);
