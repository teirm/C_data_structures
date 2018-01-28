/* Purpose: Header File for BFS implementation
 * Author:  Cyrus Ramavarapu
 * Date:    28 January 2018
 */


#include "../../adjacency_list.h"
#include "../../adjacency_read_graph.h"
#include "../../../queue/queue.h"

typedef struct bfs_info_s {
    int     mark_count;
    int     *marked;
} bfs_info_s;

typedef struct graph_queue_node_s {
    struct node      *gnode;
    queue_node_t    graph_queue_link;
} graph_queue_node_t;

int
graph_adj_list_run_bfs(
    int                 vertex,
    queue_holder_t      *bfs_queue,
    adjacency_list      *a_list,
    bfs_info_s          *bfs_info);

int
graph_adj_list_start_bfs(
    int                 start_vertex,
    adjacency_list      *a_list,
    bfs_info_s          *bfs_info);
