/*
 * Author:  Cyrus Ramavarapu
 * Date:    27 January 2018
 * Purpose: Implementation of Queue
 */

#include "queue.h"

int
queue_enqueue(
    queue_holder_t      *queue,
    void                *elem,
    size_t              offset)
{
    
    if (queue == NULL) {
        return 1;
    }
    
    if (queue->last == NULL) {
        queue->first = elem + offset;
        queue->last = queue->first;
    } else {
        queue->last->next = elem + offset;
    }
    queue->size++; 

    return 0;
}

void*
queue_dequeue(
    queue_holder_t      *queue,
    size_t              offset)
{
    queue_node_t    *return_node; 
    
    if (queue == NULL) {
        return NULL;
    } 
    
    if (queue_length(queue) == 0) {
        return NULL;
    }
    
    return_node = queue->first;
    queue->first = queue->first->next;
    return_node->next = NULL;
    queue->size--;

    if (queue->size == 0) {
        queue->last == NULL;
    }
    
    return return_node - offset;
}
