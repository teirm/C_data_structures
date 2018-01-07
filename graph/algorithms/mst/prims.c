/* Purpose: Implementation of Prims Algorithm
 *          for finding the MST.
 * Author:  Cyrus Ramavarapu
 * Date:    06 January 2018
 */

#include <stdio.h>
#include <stdlib.h>

#include "prims.h"



int
graph_adj_list_prims_runner(
    adjacency_list          *a_list,
    prims_info_s            *prims_info)
{
    return 0;
}


int
main(
    int                     argc,
    char                    **argv)
{
    adjacency_list          *a_list = NULL; 
    prims_info_s            *prims_info = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: prims <weighted_undirected_graph_file>\n");
        return 1;
    }

    a_list = graph_adj_list_read_weighted_undirected_graph_file(argv[1]);
    
    if (a_list == NULL) {
        fprintf(stderr, "Error: unable to process graph file %s\n",
                argv[1]);
        return 1;
    }
    
    prims_info = calloc(1, sizeof(*prims_info));

    if (prims_info == NULL) {
        fprintf(stderr, "Error: Out of Memory\n");
        return 1;
    }
    
    prims_info->marked = calloc(a_list->vertices, sizeof(int));

    if (!prims_info->marked) {
        fprintf(stderr, "Error: Out of Memory\n");
        return 1;
    }
    
    return graph_adj_list_prims_runner(a_list, prims_info);
}
