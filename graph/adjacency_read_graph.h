/* Header file to read a graph into an
 * adjacency list.
 */

#include "adjacency_list.h"

adjacency_list *
graph_adj_list_initialize_alist(
    int                             total_vertices);

int
graph_adj_list_read_graph(
    char *file_name);

