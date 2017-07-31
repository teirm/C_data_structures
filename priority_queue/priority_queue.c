/* 
 * Purpose: Implementation of the priority 
 *          Queue.
 *
 * Author: Cyrus Ramavarapu
 * Date: 24 July 2017
 */


#include <stdlib.h>

#include "priority_queue.h"

#define DEBUG 1

#if DEBUG
#include <stdio.h>
#include <ds/debug.h>
#define VOID_TO_INT(x) *(int *)(x)
#endif

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

    return 0;
}

struct priority_node *
delete_min(
        struct priority_queue       *pq) {
    int curr_pos                            = 0; 
    int last_pos                            = 0;

    struct priority_node *return_node       = NULL;
    struct priority_node **queue            = pq->root;


    if (pq->root[0] == NULL) {
#if DEBUG
        printf("[%s:%d] pq->root[0] == %p\n",
                DEBUG_INFO, pq->root[0]);
#endif
        /* Attempting to delete out of an empty tree */ 
        return NULL;
    }

    return_node = queue[0];
    last_pos = pq->last_node - 1;
   
    queue[0] = queue[last_pos];
    queue[last_pos] = NULL;
    pq->last_node--;

    /* Float new root value down */
    /* NOTE: This feels buggy especially on the edge cases:
     *       float down to original position?
     *       float past end of array?
     */
    while (curr_pos < pq->last_node) {
        if (queue[curr_pos]->priority > queue[2*curr_pos+1]->priority) {
            swap(queue[curr_pos], queue[2*curr_pos+1]);
            curr_pos = 2*curr_pos + 1;
#if DEBUG
        printf("[%s:%d] Swapping A: %p and B: %p\n" \
               "\tA->priority: %d A->value: %d A pos: %d"\
               "\tB->priority: %d B->value: %d B pos: %d",
               DEBUG_INFO, queue[2*curr_pos+1], queue[curr_pos],
               queue[2*curr_pos+1]->priority, 
               VOID_TO_INT(queue[2*curr_pos+1]->value),
               2*curr_pos+1,
               queue[curr_pos]->priority,
               VOID_TO_INT(queue[curr_pos]->value),
               curr_pos);

#endif
        } else if (queue[curr_pos]->priority > queue[2*curr_pos+2]->priority) {
            swap(queue[curr_pos], queue[2*curr_pos+2]);
            curr_pos = 2*curr_pos + 2;
#if DEBUG
            printf("[%s:%d] Swapping A: %p and B: %p\n" \
                   "\tA->priority: %d A->value: %d A pos: %d\n"\
                   "\tB->priority: %d B->value: %d B pos: %d\n",
                   DEBUG_INFO, queue[2*curr_pos+2], queue[curr_pos],
                   queue[2*curr_pos+2]->priority, 
                   VOID_TO_INT(queue[2*curr_pos+2]->value),
                   2*curr_pos+2,
                   queue[curr_pos]->priority,
                   VOID_TO_INT(queue[curr_pos]->value),
                   curr_pos);

#endif
        } else {
            /* found heap property location */
#if DEBUG
            printf("[%s:%d] Position Found at: %d\n" \
                    "\tPriority Node: %p Priority: %d Value: %d\n",
                    DEBUG_INFO, curr_pos, queue[curr_pos],
                    queue[curr_pos]->priority,
                    VOID_TO_INT(queue[curr_pos]->value));

#endif 
            break;
        }
    }

    return return_node;
}


int
resize(
        struct priority_queue       *pq)
{
    int i; 
    int new_size                    = 2 * pq->size;
    struct priority_node **new_root = NULL;

    new_root = calloc(new_size, sizeof *new_root);
   
    if (new_root == NULL) {
        /* Failed to allocate a new root */ 
        return 1;
    }

    for (i = 0; i < pq->size; ++i) {
        new_root[i] = pq->root[i];
    }
    
    free(pq->root);
    pq->root = new_root;
    
    return 0;
}


int
insert(
        struct priority_queue       *pq,
        struct priority_node        *pn)
{
    int curr_position                = 0;
    int rc                           = 0;

    struct priority_node **queue     = pq->root;

    if (pq->last_node + 1 == pq->size) {
        rc = resize(pq);
        if (rc) {
            /* The resize operation failed */ 
            return 1;
        }
    }

    curr_position = pq->last_node; 
    queue[curr_position] = pn;
    pq->last_node++; 

    /* Float up the new node */
    while (curr_position > 0) {
        if (queue[curr_position / 2]->priority > queue[curr_position]->priority) {
            swap(queue[curr_position / 2], queue[curr_position]); 
            curr_position /= 2;
#if DEBUG
        printf("[%s:%d] Swapping A: %p and B: %p\n" \
               "\tA->priority: %d A->value: %d A pos: %d\n"\
               "\tB->priority: %d B->value: %d B pos: %d\n",
               DEBUG_INFO, queue[curr_position/2], queue[curr_position],
               queue[curr_position/2]->priority, 
               VOID_TO_INT(queue[curr_position/2]->value),
               curr_position/2,
               queue[curr_position]->priority,
               VOID_TO_INT(queue[curr_position]->value),
               curr_position);
#endif
        } else {
            /* Found position satisfying heap property */
#if DEBUG
            printf("[%s:%d] Position Found at: %d\n" \
                    "\tPriority Node: %p Priority: %d Value: %d\n"\
                    "\tPosition: %d\n",
                    DEBUG_INFO, curr_position, pn,
                    pn->priority, VOID_TO_INT(pn->value),
                    curr_position);
#endif
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

