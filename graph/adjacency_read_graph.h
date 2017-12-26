/* Header file to read a graph into an
 * adjacency list.
 */

#include <limits.h>

#include "adjacency_list.h"

#define UNITIALIZED_COST INT_MAX  

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
