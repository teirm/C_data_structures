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

int
graph_trans_matrix_read_graph_file(
    char                *file_name,
    int                 track_costs)
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

    graph_file = fopen(file_name, "r");


    if (!graph_file) {
        perror("Error");
        return errno;
    }

    error_state = 1; 
    rc = fscanf(graph_file, "%d", &total_vertices);
    if (rc != 1) {
        goto read_graph_error;
    } 
    
    error_state = 2;
    rc = fscanf(graph_file, "%d", &total_edges);
    if (rc != 1) {
        goto read_graph_error;
    } 
    
    error_state = 3;
    graph_matrix = graph_trans_matrix_init_tmatrix(
            total_vertices, track_costs); 
    
    if (!graph_matrix) {
        rc = DS_ENOMEM;
        goto read_graph_error;
    }


    error_state = 4;
    while (fscanf(graph_file,
                "%d %d",
                &start_vertex,
                &end_vertex) == 2) {
        rc = graph_trans_matrix_add_entry(
                graph_matrix, start_vertex, end_vertex);
        if (rc) {
            goto read_graph_error;
        }

        if (track_costs) {
            error_state = 6;
            
            rc = fscanf(graph_file,
                    "%d",
                    &edge_cost);

            if (rc != 1) {
                goto read_graph_error;
            }
        
            graph_matrix->cost_matrix[start_vertex][end_vertex] =
                edge_cost;
        }
    }
    
    fclose(graph_file);
    graph_trans_matrix_free_tmatrix(graph_matrix,
            total_vertices);
    return 0;
read_graph_error:
    switch (error_state) {
        case 4:
            fprintf(stderr, "Error with file %s: \
                    Failed to add entry to graph matrix\n",
                    file_name);
            fclose(graph_file);
            graph_trans_matrix_free_tmatrix(graph_matrix, 
                    total_vertices);
            break;
        case 3:
            fprintf(stderr, "Error with file %s: \
                    Failed to init graph matrix\n",
                    file_name);
            fclose(graph_file);
            break;
        case 2:
            fprintf(stderr, "Error with file %s: \
                    Failed to read total edges\n",
                    file_name);
            fclose(graph_file);
            break;
        case 1:
            fprintf(stderr, "Error with file %s: \
                    Failed to read total vertices\n",
                    file_name);
            fclose(graph_file);
            break;
        default: /* error_state == 0 */
            perror("Error");
            break;
    }
    return rc;

}

int main(
    int                 argc,
    char                **argv)
{
    if (argc != 2) {
        printf("Usage: ./transition_read_graph <file_name>\n");
        return 1;
    }
    return graph_trans_matrix_read_graph_file(argv[1], FALSE);
}


