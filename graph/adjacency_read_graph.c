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
 *
 *       Example:
 *       3
 *       2
 *       1 2
 *       1 3
 */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "adjacency_read_graph.h"
#include "adjacency_list.h"

int
adj_read_graph(
    char *file_name)
{
    int vertices = 0;
    int edges = 0;
  
    int start_vertex = 0;
    int end_vertex = 0;

    int e_count = 0;
    int rc = 0; 


    adjacency_list *a_list = NULL;

    FILE *graph_file = NULL;

    graph_file = fopen(file_name, "r");

    if (!graph_file) {
        perror("Error");
        return 1;
    }
    
    rc = fscanf(graph_file, "%d", &vertices);
    rc = fscanf(graph_file, "%d", &edges);

    a_list = calloc(1, sizeof *a_list);
    a_list->vertices = vertices;
    a_list->list_array = calloc(vertices, sizeof *(a_list->list_array));

    printf("Vertices: %d\nEdges: %d\n",
            vertices, edges);

    while (fscanf(graph_file,
                  "%d %d",
                  &start_vertex,
                  &end_vertex) == 2) {
        
        e_count++;
        if (e_count > edges) {
            fprintf(stderr,
                    "Error processing file %s: Too many vertices\n",
                    file_name);
            fclose(graph_file);
            return 1;
        }

        /* Need to recall if the a list worked by 
         * using array index and then each link would
         * be an adjacent vertex or if something more
         * complicated.
         */

        /* It would be a good idea to also check for
         * duplicates and have some policy regarding
         * how to handle them.  For the time being
         * I will not be dealing with the multigraphs.
         */

        printf("%d -> %d\n", start_vertex, end_vertex);
    }

    
    return 0;
}

int
main(
    int argc,
    char **argv)
{

    if (argc != 2) {
        printf("Usage: ./read_graph <file_name>\n");
        return 1;
    }
    
    adj_read_graph(argv[1]);

    return 0;
}



