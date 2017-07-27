/*
 * Purpose: Priority Queue Implementation.
 *          
 * 
 * Author: Cyrus Ramavarapu
 * Date: 24 July 2017
 */

#ifndef PRIORITY_QUEUE_GUARD
#define PRIORITY_QUEUE_GUARD

#include <stdlib.h>


struct priority_node {
    int priority;                           /* Priority of the node -- int for convenience */
    int index;                              /* Index of the node */ 
    void *value;                            /* Value held by the node */ 
    
};

struct priority_queue {
    struct priority_node **root;             /* Pointer to the root of the tree */
    int last_node;                           /* Value of the last node */
    int size;                                /* Max size of priority queue */
};

/* Delete and return the node with the highest priority */
struct priority_node *delete_min(struct priority_queue *pq);

/* Insert a node with some priority into the tree */
int insert(struct priority_queue *pq, struct priority_node *pn);

/* Swap the priorities and values of two nodes */
int swap(struct priority_node *a, struct priority_node *b);

/* Delete all nodes from the tree */
int delete_tree(struct priority_queue *pq, void (*free_value)(void *value));
#endif 
