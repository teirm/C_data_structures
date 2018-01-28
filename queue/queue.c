/*
 * Author:  Cyrus Ramavarapu
 * Date:    27 January 2018
 * Purpose: Implementation of Queue
 */

#include <stdio.h>
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
        printf("elem: %p, offset: %lu, elem+offset: %p\n",
                elem, offset, elem+offset);
        queue->last = queue->first;
    } else {
        queue->last->next = elem + offset;
        queue->last = elem + offset;
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
        queue->last = NULL;
    }
    
    printf("return_node: %p, offset: %lu, return_node-offset: %p\n",
            return_node, offset, (void*)return_node - offset);
    
    return (void *)return_node - offset; // need to cast to void prior to return don't want to do ptr_math on queue_node_t 
}
