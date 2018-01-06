/* Purpose: Header file for Prim's
 *          Algorithm 
 * Author: Cyrus Ramavarapu
 * Date:   06 January 2018
 */

#include "../../adjacency_list.h"
#include "../../adjacency_read_graph.h"

typedef struct prims_info_s {
    int total_cost;
    int *marked;
} prims_info_s;


int
graph_adj_list_prims_runner(
    adjacency_list              *a_list,
    prims_info_s                *prims_info);

int
graph_adj_list_prims_closest(
    int                         vertex,
    adjacency_list              *a_list,
    prims_info_s                *prims_info);

int 
graph_adj_list_prims_low_cost(
    int                         vertex,
    adjacency_list              *a_list,
    prims_info_s                *prims_info);


