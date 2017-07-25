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
    void *value;                            /* Value held by the node */ 
    
    struct priority_node *parent;           /* Point to the parent -- useful for deletions */
    struct priority_node *left_child;       /* Pointer to the left child */
    struct priority_node *right_child;      /* Pointer to the right child */
};

struct priority_queue {
    struct priority_node *root;             /* Pointer to the root of the tree */
    struct priority_node *next_delete;      /* Pointer to the next node to use on delete_min */
    struct priority_node *next_insert;      /* Pointer to the parent where next insertion will occur */
};

/* Delete and return the node with the highest priority */
struct priority_node *delete_min(struct priority_queue *pq);

/* Insert a node with some priority into the tree */
int insert(struct priority_queue *pq, struct priority_node *pn);

/* get the right most leaf from the previous parent */
struct priority_node *right_most_leaf(struct priority_node *pn);

/* get parent with right most null */
struct priority_node *right_most_null(struct priority_node *pn); 

/* Swap the priorities and values of two nodes */
int swap(struct priority_node *a, struct priority_node *b);

/* Delete all nodes from the tree */
int delete_tree(struct priority_queue *pq);
#endif 
