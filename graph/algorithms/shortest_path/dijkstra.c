/* Purpose: Implementation of Dijkstra's single
 *          source shortest path algorithm.
 * Author:  Cyrus Ramavarapu
 * Date:    11 November 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <ds/debug.h>

#include "dijkstra.h"

int 
main_dijkstra(
    char                *file_name,
    int                 start_vertex)
{   
    int                 i;               
    unsigned long       total_vertices = 0; 
    
    adjacency_list      *a_list = NULL; 
    dijkstra_info_s     *dijk_info = NULL;        
    
    a_list = graph_adj_list_read_graph_file(
                file_name,
                TRUE);

    if (a_list == NULL) {
        return 1;
    }
    
    total_vertices = a_list->vertices;
    dijk_info = calloc(1, sizeof *dijk_info);

    if (dijk_info == NULL) {
        return DS_ENOMEM;
    }
    
    dijk_info->seen_array = calloc(
            total_vertices,
            sizeof *(dijk_info->seen_array));
    dijk_info->distance_array = calloc(
            total_vertices,
            sizeof *(dijk_info->distance_array));
 
    
    /* Initialize distnace array with costs */
    for (i = 0; i < total_vertices; ++i) {
        dijk_info->distance_array[i] = 
            a_list->cost_matrix[start_vertex][i];
    }

    /* always start with the first vertex */
    dijk_info->seen_array[start_vertex] = 1;
}


int
main(
    int         argc,
    char        **argv)
{
    if (argc != 4) {
        printf("Usage: ./dijkstra <graph_file> <start_vertex>");
        return 1;
    }

    main_dijkstra(argv[1], atoi(argv[2]));
    
    return 0;
}


