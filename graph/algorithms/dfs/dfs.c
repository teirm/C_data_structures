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
graph_adj_list_dfs(
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
#endif
    dfs_info->mark_count++;
    for (current_neighbor = a_list->list_array[vertex];
         current_neighbor != NULL;
         current_neighbor = current_neighbor->next) {
        
        next_vertex = current_neighbor->value;
        
        if (!dfs_info->marked[next_vertex->index]) {
            graph_adj_list_dfs(next_vertex->index,
                    a_list,
                    dfs_info);
        }
    }
    return 0;
}


int
main(
    int         argc,
    char        **argv)
{
    adjacency_list      *a_list = NULL;    
    dfs_info_s          *dfs_info = NULL; 

    if (argc != 2) {
        printf("Usage: dfs <graph_file>\n");
        return 1;
    }
   
    a_list = graph_adj_list_read_graph_file(
            argv[1], FALSE);

    
    if (a_list == NULL) {
        return 1;
    }

    dfs_info = calloc(1, sizeof *dfs_info);
    
    if (dfs_info == NULL) {
        graph_adj_list_free_alist(a_list); 
        return 1;
    }

    dfs_info->marked = calloc(a_list->vertices,
                              sizeof *dfs_info->marked);

    
    if (dfs_info->marked == NULL) {
        free(dfs_info);
        graph_adj_list_free_alist(a_list);
        return 1;
    }
    
    graph_adj_list_dfs(0, a_list, dfs_info);
   
    return 0;
}

