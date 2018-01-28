/* Author: Cyrus Ramavarapu
 * Date:   27 January 2018
 * Purpose: Test squite for queue
 */

#include <stdio.h>
#include <stdlib.h>
#include "../queue.h"


#define TEST_ELEMENTS 100

typedef struct test_struct_s {
    int             item;
    queue_node_t    queue_link; 
} test_struct_t;

int
populate_test_array(
    test_struct_t       **test_array,
    int                 size)
{
    int i = 0;
    
    for (int i = 0; i < size; ++i) {
        test_array[i] = calloc(1, sizeof(test_struct_t));
        test_array[i]->queue_link.next = NULL;
    }

    return 0;
}
                



int main()
{
    int i;    
    size_t vm_offset = struct_offset(struct test_struct_s, queue_link); 
    queue_holder_t test_queue;
    queue_node_t   link;
    test_struct_t test_element;
    test_struct_t *return_element;
    
    test_struct_t* test_array[TEST_ELEMENTS];

    populate_test_array(test_array, TEST_ELEMENTS);
    
    printf("test_array[0]->item: %d\ntest_array[0]->queue_link: %p\n", 
           test_array[10]->item, &test_array[10]->queue_link);

    link.next = NULL;

    test_queue.first = NULL;
    test_queue.last = NULL;
    test_queue.size = 0;
    
    test_element.item = 1231213;
    test_element.queue_link = link; 

    printf("Vmoffset: %lu\n", vm_offset);

    queue_enqueue(&test_queue, &test_element, vm_offset);
    
    printf("Queue size is now %d\n", queue_length(&test_queue));

    return_element = queue_dequeue(&test_queue, vm_offset);
    
    printf("Return element: %d\n", return_element->item);
    
    printf("Queue.first: %p\n", test_queue.first);
    printf("Queue.last: %p\n", test_queue.last);
    printf("Queue size is now %d\n", queue_length(&test_queue));
    

    return 0;
}



