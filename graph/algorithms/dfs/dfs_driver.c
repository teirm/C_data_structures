/* Purpose: Driver for DFS implementation
 *          on adjacency lists
 * Author:  Cyrus Ramavarapu
 * Date:    12 March 2018
 */

#include <stdio.h>
#include <stdlib.h>

#include "dfs.h"

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
