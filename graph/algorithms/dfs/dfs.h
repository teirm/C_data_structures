/* Purpose: Header file for depth first
 *          search implementation.
 * Author:  Cyrus Ramavarapu
 * Date:    11 November 2017
 */

#include "../../transition_matrix.h"
#include "../../adjacency_list.h"
#include "../../adjacency_read_graph.h"

typedef struct dfs_info_s {
    int     mark_count;
    int     *marked;
} dfs_info_s;

int
graph_adj_list_run_dfs(
    int                 vertex, 
    adjacency_list      *a_list,
    dfs_info_s          *dfs_info);


int
graph_adj_list_start_dfs(
    int                  start_vertex,
    adjacency_list      *a_list,
    dfs_info_s          *dfs_info);


