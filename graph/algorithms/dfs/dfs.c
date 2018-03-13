/* Purpose: Implementation of depth first
 *          search
 * Author: Cyrus Ramavarapu
 * Date: 26 December 2017
 */

#include <stdio.h>

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


