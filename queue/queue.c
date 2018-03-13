/*
 * Author:  Cyrus Ramavarapu
 * Date:    27 January 2018
 * Purpose: Implementation of Queue
 */

#include <stdio.h>
#include <ds/debug.h>

#include "queue.h"

#define QUEUE_DEBUG() 0

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
#if QUEUE_DEBUG() > 0
        printf("elem: %p, offset: %lu, elem+offset: %p\n",
                elem, offset, elem+offset);
#endif /* QUEUE_DEBUG() > 0 */
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
#if QUEUE_DEBUG() > 0
    printf("return_node: %p, offset: %lu, return_node-offset: %p\n",
            return_node, offset, (void*)return_node - offset);
#endif /* QUEUE_DEBUG() > 0 */

    /* need to cast to void prior to returning since
     * the ptr_math should not be done on the
     * queue_node_t
     */
    return (void *)return_node - offset; 
}
