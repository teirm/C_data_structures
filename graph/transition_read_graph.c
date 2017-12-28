/* Purpose: Read file into a transition matrix
 *          for graph analysis.
 * Author:  Cyrus
 * Date:    23 October 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <ds/debug.h>

#include "transition_read_graph.h"


int
graph_trans_matrix_free_tmatrix(
    t_matrix                    *graph_matrix,
    int                         total_vertices)
{
    int row;
    int col;

    for (row = 0; row < total_vertices; ++row) {
        for (col = 0; col < total_vertices; ++col) {
            if (graph_matrix->matrix[row][col]) {
                free(graph_matrix->matrix[row][col]);
            }
        }
        free(graph_matrix->matrix[row]);
    }
    free(graph_matrix->matrix);
    
    if (graph_matrix->cost_matrix) { 
        for (row = 0; row < total_vertices; ++row) {
            if (graph_matrix->cost_matrix[row]) {
                free(graph_matrix->cost_matrix[row]);
            }
        }
        free(graph_matrix->cost_matrix);
    }
    free(graph_matrix);
    return 0;
}

t_matrix *
graph_trans_matrix_init_tmatrix(
    int                         total_vertices,
    int                         track_costs)
{   
    int i;
    int j;
    t_matrix                    *graph_matrix = NULL;
    
    graph_matrix = calloc(1, sizeof *graph_matrix);
    
    if (!graph_matrix) {
        return NULL;
    }
    
    graph_matrix->matrix = calloc(total_vertices,
            sizeof *graph_matrix->matrix);
    
    if (!graph_matrix->matrix) {
        return NULL;
    }

    for (i = 0; i < total_vertices; ++i) {
        graph_matrix->matrix[i] = 
            calloc(total_vertices, sizeof *graph_matrix->matrix[i]);
        
        if (!graph_matrix->matrix[i]) {
            for (j = i - 1; j >= 0; --j) {
                free(graph_matrix->matrix[j]);
            }
            return NULL;
        }
    }
    
    return graph_matrix;
}

int
graph_trans_matrix_add_entry(
    t_matrix                *graph_matrix,
    int                     start_vertex,
    int                     end_vertex)
{
    graph_node              *matrix_entry = NULL;

    matrix_entry = calloc(1, sizeof *matrix_entry);
    if (!matrix_entry) {
        return DS_ENOMEM;
    }
   
    matrix_entry->index = end_vertex;

    graph_matrix->matrix[start_vertex][end_vertex] =
        matrix_entry;
    return 0;
}

t_matrix *
graph_trans_matrix_read_directed_graph_file(
    char                    *file_name)
{
    return graph_trans_matrix_generic_read_graph_file(
            FALSE, FALSE, file_name);
}

t_matrix *
graph_trans_matrix_read_weighted_directed_graph_file(
    char                    *file_name)
{
    return graph_trans_matrix_generic_read_graph_file(
            TRUE, FALSE, file_name);
}

t_matrix *
graph_trans_matrix_read_undirected_graph_file(
    char                    *file_name)
{
    return graph_trans_matrix_generic_read_graph_file(
            FALSE, TRUE, file_name);
}

t_matrix *
graph_trans_matrix_read_weighted_undirected_graph_file(
    char                    *file_name)
{
    return graph_trans_matrix_generic_read_graph_file(
            TRUE, TRUE, file_name);
}

t_matrix *
graph_trans_matrix_generic_read_graph_file(
    int                 weighted,
    int                 undirected,
    char                *file_name)
{   
    int                 total_vertices = 0;
    int                 total_edges = 0;
    int                 start_vertex = 0;
    int                 end_vertex = 0;
    int                 edge_cost = 0; 
    int                 rc = 0;
    int                 error_state = 0;

    FILE                *graph_file = NULL;
    t_matrix            *graph_matrix = NULL;

    error_state = 1; 
    graph_file = fopen(file_name, "r");
    if (!graph_file) {
        goto read_graph_error;     
    }

    error_state = 2; 
    rc = fscanf(graph_file, "%d", &total_vertices);
    if (rc != 1) {
        goto read_graph_error;
    } 
    
    error_state = 3;
    rc = fscanf(graph_file, "%d", &total_edges);
    if (rc != 1) {
        goto read_graph_error;
    } 
    
    error_state = 4;
    graph_matrix = graph_trans_matrix_init_tmatrix(
            total_vertices, weighted); 
    
    if (!graph_matrix) {
        rc = DS_ENOMEM;
        goto read_graph_error;
    }


    error_state = 5;
    
    if (weighted) {
        while (fscanf(graph_file,
                    "%d %d %d",
                    &start_vertex,
                    &end_vertex,
                    &edge_cost) == 3) {
            rc = graph_trans_matrix_add_entry(
                    graph_matrix, start_vertex, end_vertex);
            if (rc) {
                goto read_graph_error;
            }

            if (undirected) {
                rc = graph_trans_matrix_add_entry(
                        graph_matrix, end_vertex, start_vertex);
            
                if (rc) {
                    goto read_graph_error;
                }
            }
            
            error_state = 6;
            if (edge_cost >= COST_MAX) {
                goto read_graph_error;
            }

            graph_matrix->cost_matrix[start_vertex][end_vertex] =
                edge_cost;
            if (undirected) {
                graph_matrix->cost_matrix[end_vertex][start_vertex] = 
                    edge_cost;
            }
        }
    } else { 
        while (fscanf(graph_file,
                    "%d %d",
                    &start_vertex,
                    &end_vertex) == 2) {
            rc = graph_trans_matrix_add_entry(
                    graph_matrix, start_vertex, end_vertex);
            if (rc) {
                goto read_graph_error;
            }

            if (undirected) {
                rc = graph_trans_matrix_add_entry(
                        graph_matrix, end_vertex, start_vertex);
                if (rc) {
                    goto read_graph_error;
                }
            }
        }
    }

    return graph_matrix;

read_graph_error:
    switch (error_state) {
        case 6:
            fprintf(stderr, "Error with file %s: \
                    Edge cost greater than max (%d)\n",
                    file_name, COST_MAX);
            fclose(graph_file);
            graph_trans_matrix_free_tmatrix(graph_matrix,
                    total_vertices);
            break;
        case 5:
            fprintf(stderr, "Error with file %s: \
                    Failed to add entry to graph matrix\n",
                    file_name);
            fclose(graph_file);
            graph_trans_matrix_free_tmatrix(graph_matrix, 
                    total_vertices);
            break;
        case 4:
            fprintf(stderr, "Error with file %s: \
                    Failed to init graph matrix\n",
                    file_name);
            fclose(graph_file);
            break;
        case 3:
            fprintf(stderr, "Error with file %s: \
                    Failed to read total edges\n",
                    file_name);
            fclose(graph_file);
            break;
        case 2:
            fprintf(stderr, "Error with file %s: \
                    Failed to read total vertices\n",
                    file_name);
            fclose(graph_file);
            break;
        case 1: /* error_state == 0 */
            perror("Error");
            break;
    }
    return NULL;
}


