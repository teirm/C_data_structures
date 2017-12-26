/* Purpose: Header file for implementation of 
 *          Dijkstra's single source shortest
 *          path algorithm.
 * Author:  Cyrus Ramavarapu
 * Date:    11 November 2017
 */

#include "../../transition_matrix.h"
#include "../../adjacency_list.h"
#include "../../adjacency_read_graph.h"

typedef struct dijkstra_info_s {
    unsigned int    *seen_array;
    unsigned int    *distance_array;
} dijkstra_info_s;

int
graph_adj_list_dijkstra(
    adjacency_list      *a_list,
    dijkstra_info_s     *dijk_info);

int
graph_trans_matrix_dijkstra(
    t_matrix            *graph_matrix,
    dijkstra_info_s     *dijk_info);

int
main_dijkstra(
    char                *file_name,
    int                 start_vertex);

int
display_results(
    dijkstra_info_s    *dijk_info);


