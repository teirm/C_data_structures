/* Purpose: Implementation of Dijkstra's single
 *          source shortest path algorithm.
 * Author:  Cyrus Ramavarapu
 * Date:    11 November 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

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
    
    dijk_info->vertices = total_vertices;
    dijk_info->visited = calloc(
            total_vertices,
            sizeof *(dijk_info->visited));
    dijk_info->distances = calloc(
            total_vertices,
            sizeof *(dijk_info->distances));
 
    
    /* Initialize distnace array with costs */
    for (i = 0; i < total_vertices; ++i) {
        dijk_info->distances[i] = 
            a_list->cost_matrix[start_vertex][i];
    }

    /* always start with the first vertex */
    dijk_info->visited[start_vertex] = 1;

}

int
graph_adj_list_dijkstra(
    adjacency_list      *a_list,
    dijkstra_info_s     *dijk_info)
{
    int                 i;
    unsigned long       total_vertices = a_list->vertices;
    for (i = 0; i < total_vertices - 1; ++i) {
        /* NO-OP */             
    }

    return 0;
}

int
update_distances_from_difference(
    int                 new_vertex,
    adjacency_list      *a_list,
    dijkstra_info_s     *dijk_info)
{
    int                 i;
    unsigned long       total_vertices = dijk_info->vertices;

    for (i = 0; i < total_vertices - 1; ++i) {
        if (!dijk_info->visited[i]) {
            /* NOTE THIS WILL CREATE INT OVERFLOW ISSUES */ 
            dijk_info->distances[i] = min(dijk_info->distances[i], 
                    dijk_info->distances[i] + a_list->cost_matrix[new_vertex][i]);
        }
    }
}

int
get_min_unvisited_vertex(
    dijkstra_info_s     *dijk_info)
{
    int                 i;
    int                 min_vertex = 0; 
    int                 min_dist = INT_MAX;
    unsigned long       total_vertices = dijk_info->vertices; 
   
    /* Since we will find a vertex that a min weight,
     * it must be connected to the already growing tree.
     */
    for (i = 0; i < total_vertices - 1; ++i) {
        if (!dijk_info->visited[i] 
            && dijk_info->distances[i] < min_dist) {
            min_dist = dijk_info->distances[i];
            min_vertex = i;
        }
    }
    return min_vertex;
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


