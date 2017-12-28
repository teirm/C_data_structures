/* Purpose: Implementation of depth first
 *          search
 * Author: Cyrus Ramavarapu
 * Date: 26 December 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <ds/debug.h>

#include "dfs.h"

#define DFS_DEBUG 1


int
graph_adj_list_run_dfs(
    int                 vertex, 
    adjacency_list      *a_list,
    dfs_info_s          *dfs_info)
{
    /* Linked list for the neighbors */
    graph_node          *next_vertex = NULL;  
    struct node         *current_neighbor = NULL;

    dfs_info->marked[vertex] = 1;
#if DFS_DEBUG
    printf("[%s:%d] marking vertex %d\n",
            DEBUG_INFO, vertex);
#endif /* DFS_DEBUG */
    dfs_info->mark_count++;
    for (current_neighbor = a_list->list_array[vertex];
         current_neighbor != NULL;
         current_neighbor = current_neighbor->next) {
        
        next_vertex = current_neighbor->value;
        
        if (!dfs_info->marked[next_vertex->index]) {
            graph_adj_list_run_dfs(next_vertex->index,
                    a_list,
                    dfs_info);
        }
    }
    return 0;
}

int
graph_adj_list_start_dfs(
    int                 start_vertex,
    adjacency_list      *a_list,
    dfs_info_s          *dfs_info)
{
    int                 vertex;
    int                 total_vertices = a_list->vertices;
    
    graph_adj_list_run_dfs(start_vertex, a_list, dfs_info);

    /* Need to pick an unmarked vertex in case all
     * vertices were not reachable on a single pass.
     */
    while (total_vertices != dfs_info->mark_count) {
        /* Pick an unmarked vertex */
        for (vertex = 0; vertex < total_vertices; ++vertex) {
            if (!dfs_info->marked[vertex]) {
                break;
            }
        }
#if DFS_DEBUG
        printf("[%s:%d] Restarting dfs with vertex %d\n",
                DEBUG_INFO, vertex);
#endif /* DFS_DEBUG */
        graph_adj_list_run_dfs(vertex, a_list, dfs_info);
    }
    return 0;
}

int
main(
    int         argc,
    char        **argv)
{
    int                 error_state = 0;
    int                 start_vertex = 0;
    adjacency_list      *a_list = NULL;    
    dfs_info_s          *dfs_info = NULL; 

    if (argc != 3) {
        printf("Usage: dfs <graph_file> <start_vertex>\n");
        return 1;
    }
   

    error_state = 1;
    a_list = graph_adj_list_read_directed_graph_file(
            argv[1]);

    
    if (a_list == NULL) {
        goto init_error;
    }
    
    error_state = 2;
    start_vertex = atoi(argv[2]);
    
    if (start_vertex < 0 || start_vertex > a_list->vertices) {
        goto init_error;
    }

    dfs_info = calloc(1, sizeof *dfs_info);
    
    if (dfs_info == NULL) {
        goto init_error; 
    }

    error_state = 3; 
    dfs_info->marked = calloc(a_list->vertices,
                              sizeof *dfs_info->marked);

    if (dfs_info->marked == NULL) {
        goto init_error; 
    }
    
    graph_adj_list_start_dfs(start_vertex, a_list, dfs_info);
    return 0;

/* Rollback allocations in case of any errors */
init_error:
    switch (error_state) {
        case 3:
            free(dfs_info);
            /* FALLTHROUGH */
        case 2:
            graph_adj_list_free_alist(a_list);
            /* FALLTHROUGH */
        case 1: 
            fprintf(stderr, "Error %d during dfs initialization\n",
                error_state);
            break;
    }
    return error_state;
}

