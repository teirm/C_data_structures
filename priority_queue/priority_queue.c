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
    struct priority_node **new_root = NULL;

    new_root = calloc(2*pq->size, sizeof *new_root);
   
    if (new_root == NULL) {
        /* Failed to allocate a new root */ 
        return 1;
    }

    for (i = 0; i < pq->size; ++i) {
        new_root[i] = pq->root[i];
#if DEBUG
        printf("[%s:%d] new_root[%d]: %p\n"\
               "\tpq->root[%d]: %p\n",
               DEBUG_INFO, i, new_root[i],
               i, pq->root[i]);
#endif
    }
    
    free(pq->root);
    pq->root = new_root;
    pq->size = 2*pq->size;


    return 0;
}


int
insert(
        struct priority_queue       *pq,
        struct priority_node        *pn)
{
    int curr_position                   = 0;
    int offset                          = 0;
    int rc                              = 0;

    struct priority_node **queue        = pq->root;

    if (pq->last_node == pq->size) {
#if DEBUG
        printf("[%s:%d] Resizing queue\n",
                DEBUG_INFO);
#endif
        rc = resize(pq);

        if (rc) {
            /* The resize operation failed */ 
            fprintf(stderr, "[%s:%d] Queue Resize failed\n",
                    DEBUG_INFO);
            return 1;
        }

        /* Need to reassign the root on a resize */
        queue = pq->root;
    }

    curr_position = pq->last_node; 
    pq->root[curr_position] = pn;

#if DEBUG 
    printf("[%s:%d] Inserted: %p Value in queue[%d]: %p\n",
            DEBUG_INFO, pn, curr_position, pq->root[curr_position]);
#endif
    
    pq->last_node++; 
   
#if DEBUG
    printf("[%s:%d] curr_position: %d\npq->last_node: %d\n",
            DEBUG_INFO, curr_position, pq->last_node);
#endif
    

    /* Float up the new node */
    while (curr_position > 0) {
        /* Need to apply an offset to even so that the 
         * indexing works correctly.
         */
        offset = curr_position % 2 == 0 ? 1: 0;

        if (queue[curr_position / 2 - offset]->priority > queue[curr_position]->priority) {
            swap(queue[curr_position / 2 - offset], queue[curr_position]); 
#if DEBUG
        printf("[%s:%d] Swapping A: %p and B: %p\n" \
               "\tA->priority: %d A->value: %d A pos: %d\n"\
               "\tB->priority: %d B->value: %d B pos: %d\n",
               DEBUG_INFO, queue[curr_position/2-offset], queue[curr_position],
               queue[curr_position/2-offset]->priority, 
               VOID_TO_INT(queue[curr_position/2-offset]->value),
               curr_position/2-offset,
               queue[curr_position]->priority,
               VOID_TO_INT(queue[curr_position]->value),
               curr_position);
#endif
            curr_position /= 2;
            curr_position -= offset;
        } else {
            /* Found position satisfying heap property */
#if DEBUG
            printf("[%s:%d] Position Found at: %d\n" \
                    "\tPriority Node: %p Priority: %d Value: %d\n"\
                    "\tPosition: %d\n",
                    DEBUG_INFO, curr_position, pn,
                    pn->priority, VOID_TO_INT(pn->value),
                    curr_position);
            printf("[%s:%d] Value in queue[%d]: %p\n",
                    DEBUG_INFO, curr_position, queue[curr_position]);
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

