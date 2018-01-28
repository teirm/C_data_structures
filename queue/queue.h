/*
 * Author: Cyrus Ramavarapu
 * Date:   27 January 2018
 * Purpose: Header file for queue
 */

#include <stdlib.h>

typedef struct queue_node_s {
    struct queue_node_s   *next;
} queue_node_t;


typedef struct queue_holder_s {
    int            size;
    queue_node_t   *first;
    queue_node_t   *last;
} queue_holder_t;

#define struct_offset(_type_, _elem_) (size_t)&(((_type_ *)0)->_elem_)

#define queue_length(_head_) (_head_)->size

int queue_enqueue (queue_holder_t *queue, void *elem, size_t offset);
void* queue_dequeue(queue_holder_t *queue, size_t offset);



