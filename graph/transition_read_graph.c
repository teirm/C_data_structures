/* Purpose: Read file into a transition matrix
 *          for graph analysis.
 * Author:  Cyrus
 * Date:    23 October 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <ds/debug.h>

#include "transition_matrix.h"

#define check_read(rc, count, file_name) \
    if (rc != count) {\
        fprintf(stderr, "Error parsing file %s", \
                file_name);\
        return 1;\
    }


int
free_transition_matrix();


int
transition_read_graph(
    char                *file_name)
{   
    int                 i = 0;
    int                 total_vertices = 0;
    int                 total_edges = 0;

    int                 start_vertex = 0;
    int                 end_vertex = 0;
    
    int                 rc = 0;

    FILE                *graph_file = NULL;
    t_matrix            *graph_t_matrix = NULL;
    graph_node          *matrix_entry = NULL;

    graph_file = fopen(file_name, "r");

    if (!graph_file) {
        perror("Error");
        return errno;
    }

    rc = fscanf(graph_file, "%d", &total_vertices);
    check_read(rc, 1, file_name);    

    rc = fscanf(graph_file, "%d", &total_edges);
    check_read(rc, 1, file_name);

    graph_t_matrix =
        calloc(1, sizeof *graph_t_matrix);   
    
    if (!graph_t_matrix) {
        return DS_ENOMEM;
    }

    graph_t_matrix->matrix =
        calloc(total_vertices, sizeof *graph_t_matrix->matrix);

    if (!graph_t_matrix) {
        return DS_ENOMEM;
    }

    for (i = 0; i < total_vertices; i++) {
        
        graph_t_matrix->matrix[i] = 
            calloc(total_vertices, sizeof *graph_t_matrix->matrix[i]);
        
        if(!graph_t_matrix->matrix[i]) {
            return DS_ENOMEM;
        }
    }

    while (fscanf(graph_file,
                "%d %d",
                &start_vertex,
                &end_vertex) == 2) {
        
        matrix_entry = calloc(1, sizeof *matrix_entry);
        if (!matrix_entry) {
            return DS_ENOMEM;
        }

        matrix_entry->index = end_vertex;
        
        graph_t_matrix->matrix[start_vertex][end_vertex] =
            matrix_entry;
    }

    return 0;
}

int main(
    int                 argc,
    char                **argv)
{
    if (argc != 2) {
        printf("Usage: ./transition_read_graph <file_name>");
        return 1;
    }

    transition_read_graph(argv[1]);

    return 0;
}


