/* Purpose: Implementation of BFS
 * Author:  Cyrus Ramavarapu
 * Date:    28 January 2018
 */

#include "bfs.h"

int
graph_adj_list_run_bfs(
    int                 vertex,
    queue_holder_t      *bfs_queue,
    adjacency_list      *a_list,
    bfs_info_s          *bfs_info)
{
    struct node         *neighborhood_list = NULL;  
    struct node         *current_neighbor = NULL;
    size_t vm_offset = struct_offset(graph_queue_node_t, graph_queue_link);
    
    graph_queue_node_t  *queue_node = NULL;
    graph_node          *vertex_neighbor = NULL;  

    queue_node = calloc(1, sizeof(*queue_node));
    queue_node->gnode = a_list->list_array[vertex];    
    
    queue_enqueue(bfs_queue, queue_node, vm_offset);
    
    while (queue_length(bfs_queue) != 0) {
        neighborhood_list = queue_dequeue(bfs_queue, vm_offset);
        for (current_neighbor = neighborhood_list;
             current_neighbor != NULL;
             current_neighbor = current_neighbor->next) {
            
            vertex_neighbor = current_neighbor->value;
            if (!bfs_info->marked[vertex_neighbor->index]) {
                bfs_info->marked[vertex_neighbor->index] = 1;
                bfs_info->mark_count++; 
                queue_node = calloc(1, sizeof(*queue_node));
                queue_node->gnode = a_list->list_array[vertex_neighbor->index];
                queue_enqueue(bfs_queue, queue_node, vm_offset);
            }
        }
        free(neighborhood_list);
    }

    return 0;
}


int
graph_adj_list_start_bfs(
    int                 start_vertex,
    adjacency_list      *a_list,
    bfs_info_s          *bfs_info)
{ 
    int i;
    queue_holder_t      bfs_queue;

    bfs_queue.size = 0;
    bfs_queue.first = NULL;
    bfs_queue.last = NULL;

    bfs_info->marked[start_vertex] = 1;
    bfs_info->mark_count = 1;

    graph_adj_list_run_bfs(start_vertex,
                            &bfs_queue,
                            a_list,
                            bfs_info);

    while (bfs_info->mark_count != a_list->vertices) {
        /* The graph is not a singly connected component
         * so find the next unmarked vertex and begin
         * BFS there.
         */
        for (i = 0; i < a_list->vertices; ++i) {
            if (!bfs_info->marked[i]) {
                start_vertex = i;
                bfs_info->marked[i] = 1;
                bfs_info->mark_count++;
                break;
            }
        }
        graph_adj_list_run_bfs(start_vertex,
                               &bfs_queue,
                               a_list,
                               bfs_info);
    }


    return 0;
}
