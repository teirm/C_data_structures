/* Purpose: A program to read a graph
 *          into an adjacency list.
 * Author:  Cyrus
 * Date:    22 October 2017
 *
 * Note: FILE FORMAT for graphs
 *       FIRST LINE is the NUMBER OF VERTICES
 *       SECOND LINE is the NUMBER OF EDGES
 *       REMAINING LINES are the EDGES as
 *       vertex pairs.
 * Note: The vertex pairs must be in order with
 *       respect to the second vertex until issue
 *       #3 is resolved ( Link list has no sorting
 *       mechanism).
 * Note: Weights for the edges can be placed in a
 *       third column given that the track_costs
 *       flag is true.
 
 *       This means that the input file must be
 *       in the format of 
 *       3
 *       2
 *       1 2 1  
 *       2 1 3
 *       1 3 4
 *       2 3 5
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ds/debug.h>

#include "adjacency_read_graph.h"

#define DEBUG 1

int
graph_adj_list_free_alist(
    adjacency_list                  *a_list,
    int                             total_vertices)
{
    int                             vertex;
    struct node                     *current_node = NULL;

    for (vertex = 0; vertex < total_vertices; ++vertex) {
        current_node = list_delete_entry(0,
                &a_list->list_array[vertex]);
        while (current_node) {
            free(current_node->value);
            free(current_node);

            current_node = list_delete_entry(0,
                    &a_list->list_array[vertex]);
        }
    }
    free(a_list->list_array);

    /* Cost matrix is only allocated if
     * graph is weighted.
     */
    if (a_list->cost_matrix) {
        for (vertex = 0; vertex < total_vertices; ++vertex) {
            free(a_list->cost_matrix[vertex]);
        }
        free(a_list->cost_matrix);
    }

    free(a_list);

    return 0;
}

adjacency_list *
graph_adj_list_initialize_alist(
    int                             total_vertices,
    int                             track_costs)
{
    int i;
    int j;
    int k;
    int error_state = 0;
    adjacency_list *a_list = NULL;


    a_list = calloc(1, sizeof *a_list);
    if (a_list == NULL) {
        goto init_alist_error;
    }
    error_state = 1;
    a_list->vertices = total_vertices;

    error_state = 2;
    a_list->list_array = calloc(total_vertices,
            sizeof *(a_list->list_array));

    if (!a_list->list_array) {
        goto init_alist_error;
    }

    error_state = 3;
    for (i = 0; i < total_vertices; ++i) {
        a_list->list_array[i] = calloc(1,
                sizeof (a_list->list_array[i]));

        if (!a_list->list_array[i]) {
            goto init_alist_error;
        }
    }

    if (track_costs) {
        error_state = 4;
        a_list->cost_matrix = calloc(total_vertices,
                sizeof(int));

        if (!a_list->cost_matrix) {
            goto init_alist_error;
        }


        error_state = 5;
        for (j = 0; j < total_vertices; ++j) {
            a_list->cost_matrix[j] = calloc(total_vertices,
                    sizeof(int));

            if (!a_list->cost_matrix[i]) {
                goto init_alist_error;
            }

        }
    }
    return a_list;

init_alist_error:
    switch (error_state) {
        case 5:
            if (!a_list->cost_matrix[j]) {
                for (k = j - 1; k >= 0; --k) {
                    free(a_list->cost_matrix[k]);
                }
            }
            /* FALLTHROUGH */
        case 4:
            if (a_list->cost_matrix) {
                free(a_list->cost_matrix);
            }
            /* FALLTHROUGH */
        case 3:
            if (!a_list->list_array[i]) {
                for (k = i-1; k >= 0; --k) {
                    free(a_list->list_array[k]);
                }
            }
            /* FALLTHROUGH */
        case 2:
            free(a_list->list_array);
            /* FALLTHROUGH */
        case 1:
            free(a_list);
            /* FALLTHROUGH */
        default: /* error_state == 0 */
            break;
    }
    return NULL;
}

int
graph_adj_list_read_graph_file(
    char                        *file_name,
    int                         track_costs)
{
    int vertices = 0;
    int edges = 0;
    int start_vertex = 0;
    int end_vertex = 0;
    int edge_cost = 0;
    int e_count = 0;
    int rc = 0;
    int error_state = 0;
    FILE *graph_file = NULL;
    adjacency_list *a_list = NULL;

    graph_file = fopen(file_name, "r");
    if (!graph_file) {
        perror("Error");
        return 1;
    }

    error_state = 1;
    rc = fscanf(graph_file, "%d", &vertices);
    if (rc != 1) {
        goto read_graph_error;
    }

    error_state = 2;
    rc = fscanf(graph_file, "%d", &edges);
    if (rc != 1) {
        goto read_graph_error;
    }

    error_state = 3;
    a_list = graph_adj_list_initialize_alist(
            vertices,
            track_costs);

    if (!a_list) {
        goto read_graph_error;
    }

#if DEBUG
    printf("Vertices: %d\nEdges: %d\n",
            vertices, edges);
#endif /* DEBUG */
    while (fscanf(graph_file,
                  "%d %d",
                  &start_vertex,
                  &end_vertex) == 2) {

        e_count++;
        error_state = 4;
        if (e_count > edges) {
            goto read_graph_error;
        }
        error_state = 5;
        rc = graph_adj_list_add_node(start_vertex,
                                     end_vertex,
                                     NULL,
                                     a_list);

        if (rc) {
            goto read_graph_error;
        }

        if (track_costs) {
            error_state = 6;
            rc = fscanf(graph_file,
                        "%d",
                        &edge_cost);

            if (rc != 1) {
                goto read_graph_error;
            }

            a_list->cost_matrix[start_vertex][end_vertex] =
                edge_cost;

#if DEBUG
            /* C(start_vertex, end_vertex) = edge cost */
            printf("C(%d,%d)=%d\n",
                    start_vertex,
                    end_vertex,
                    edge_cost);
#endif /* DEBUG */
        }

        /* It would be a good idea to also check for
         * duplicates and have some policy regarding
         * how to handle them.  For the time being
         * I will not be dealing with the multigraphs.
         */
#if DEBUG
        printf("%d -> %d\n", start_vertex, end_vertex);
#endif /* DEBUG */
    }

    graph_adj_list_free_alist(a_list, vertices);
    fclose(graph_file);
    return 0;

read_graph_error:
    switch (error_state) {
        case 5:
            fprintf(stderr,
                    "Error in file %s: Failed to add node.\n",
                    file_name);
            graph_adj_list_free_alist(a_list, vertices);
            fclose(graph_file);
            break;
        case 4:
            fprintf(stderr,
                    "Error in file %s: Too many edge entries.\n",
                    file_name);
            graph_adj_list_free_alist(a_list, vertices);
            fclose(graph_file);
            break;
        case 3:
            fprintf(stderr,
                    "Error in file %s: Failed to create adjacency list.\n",
                    file_name);
            fclose(graph_file);
            break;
        case 2:
            fprintf(stderr,
                    "Error in file %s: Failed to read edges.\n",
                    file_name);
            fclose(graph_file);
            break;
        case 1:
            fprintf(stderr,
                    "Error in file %s: Failed to read vertices.\n",
                    file_name);
            fclose(graph_file);
            break;
        default: /* error_state == 0 */
            perror("Error");
            break;
    }
    return rc;
}

int
main(
    int argc,
    char **argv)
{
    if (argc != 3) {
        printf("Usage: ./read_graph <file_name> <cost_flag>\n");
        return 1;
    }

    graph_adj_list_read_graph_file(argv[1], atoi(argv[2]));

    return 0;
}



