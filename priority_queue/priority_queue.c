/* 
 * Purpose: Implementation of the priority 
 *          Queue.
 *
 * Author: Cyrus Ramavarapu
 * Date: 24 July 2017
 */


#include <stdlib.h>
#include <ds/debug.h>

#include "priority_queue.h"

struct priority_node *
delete_min(
        struct priority_queue       *pq)
{
    int curr_position                       = 0; 
    int last_position                       = 0;                         
    struct priority_node *return_node       = NULL;
    struct priority_node *swap_node         = NULL; 

    if (pq->root[0] == NULL) {
        /* Attempting to delete out of an empty tree */ 
        return NULL;
    }

    return_node = pq->root[0];
    last_position = pq->last_node - 1;
   
    pq->root[0] = pq->root[last_position];
    pq->root[last_position] = NULL;
    pq->last_node--;

    /* Float new root value down */
    /* NOTE: This feels buggy especially on the edge cases:
     *       float down to original position?
     *       float past end of array?
     */
    while (curr_position <= pq->last_node) {
        if (pq->root[curr_position]->priority > pq->root[2*curr_position+1]->priority) {
            swap(pq->root[curr_position], pq->root[2*curr_position+1]);
            curr_position = 2*curr_position + 1;
        } else if (pq->root[curr_position]->priority > pq->root[2*curr_position+2]->priority) {
            swap(pq->root[curr_position], pq->root[2*curr_position+2]);
            curr_position = 2*curr_position + 2;
        } else {
            /* found heap property location */
            break;
        }
    }

    return return_node;
}

/* Swap the priority and value of a and b */ 
int
swap(
        struct priority_node        *a,
        struct priority_node        *b)
{
    int temp_priority               = 0;
    void *temp_value                = NULL;
    
    temp_priority = a->priority;
    temp_value = a->value;

    a->priority = b->priority;
    a->value = b->value;

    b->priority = temp_priority;
    b->value = temp_value;

    return 1;
}

int
insert(
        struct priority_queue       *pq,
        struct priority_node        *pn)
{
    int curr_position                = 0; 

    if (pq->last_node + 1 == pq->size) {
        /* This is where resizing the pq would be nice */
        return 1;
    }

    curr_position = pq->last_node; 
    pq->root[curr_position] = pn;
    pq->last_node++; 

    /* Float up the new node */
    while (curr_position > 0) {
        if (pq->root[curr_position / 2]->priority > pq->root[curr_position]->priority) {
            swap(pq->root[curr_position / 2], pq->root[curr_position]); 
            curr_position /= 2; 
        } else {
            /* Found position satisfying heap property */
            break;
        }
    }
    
    return 0;
}


int
delete_tree(
        struct priority_queue       *pq,
        void (*free_value)(void *value))
{
    int i;     

    for (i = 0; i < pq->last_node; ++i) {
        if (free_value) {
            free_value(pq->root[i]->value);
        }

        free(pq->root[i]);
    }

    free(pq->root);

    return 0;
}

