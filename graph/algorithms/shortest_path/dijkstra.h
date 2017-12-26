/* Purpose: Header file for implementation of 
 *          Dijkstra's single source shortest
 *          path algorithm.
 * Author:  Cyrus Ramavarapu
 * Date:    11 November 2017
 */

#include "../../transition_matrix.h"
#include "../../adjacency_list.h"
#include "../../adjacency_read_graph.h"

#define min(x,y) (x < y ? x : y)

typedef struct dijkstra_info_s {
    int    vertices;
    int    *visited;
    int    *distances;
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
get_min_unvisited_vertex(
    dijkstra_info_s     *dijk_info);

void
update_distances(
    int                 new_vertex,
    adjacency_list      *a_list,
    dijkstra_info_s     *dijk_info);

void
display_results(
    dijkstra_info_s    *dijk_info);


