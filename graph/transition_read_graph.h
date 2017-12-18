/*
 * Purpose: A small program to read a
 *          file into a transition matrix.
 * Author: Cyrus
 * Date: 23 October 2017
 */


#include "transition_matrix.h"

int
graph_trans_matrix_free_tmatrix(
    t_matrix                    *graph_matrix,
    int                         total_vertices);

t_matrix *
graph_trans_matrix_init_tmatrix(
    int                         total_vertices,
    int                         track_costs);

int
graph_trans_matrix_add_entry(
    t_matrix                *graph_matrix,
    int                     start_vertex,
    int                     end_vertex);

int
graph_trans_matrix_read_graph_file(
        char    *file_name,
        int     track_costs);
