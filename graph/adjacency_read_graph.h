/* Header file to read a graph into an
 * adjacency list.
 */

#include "adjacency_list.h"

#define COST_MAX 9999  

adjacency_list *
graph_adj_list_initialize_alist(
    int                             total_vertices,
    int                             track_costs);

adjacency_list *
graph_adj_list_read_graph_file(
    char                            *file_name,
    int                             track_costs);

int
graph_adj_list_free_alist(
    adjacency_list                  *a_list,
    int                             total_vertices);
