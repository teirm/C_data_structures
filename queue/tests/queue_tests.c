/* Author: Cyrus Ramavarapu
 * Date:   27 January 2018
 * Purpose: Test squite for queue
 */

#include <stdio.h>
#include <stdlib.h>

#include <ds/debug.h>

#include "../queue.h"


#define TEST_ELEMENTS 100

typedef struct test_struct_s {
    int             item;
    queue_node_t    queue_link; 
} test_struct_t;


int main()
{
    int i = 0;
    int j = 0; 
    int last_dequeued = 0;
    int rc = 0;
    size_t vm_offset = 0;  
    queue_holder_t test_queue;
    test_struct_t *return_element = NULL;
    test_struct_t *new_element = NULL; 

    test_queue.size = 0;
    test_queue.first = NULL;
    test_queue.last = NULL;

    vm_offset = struct_offset(struct test_struct_s, queue_link); 

    for (i = 0; i < TEST_ELEMENTS; ++i) {
        new_element = calloc(1, sizeof(*new_element));
        
        if (!new_element) {
            fprintf(stderr, "[%s:%u]: calloc returned null.  OOM Error.\n",
                    DEBUG_INFO);
            rc = 1;
            break;
        }

        new_element->item = i;
        rc = queue_enqueue(&test_queue, new_element, vm_offset);
        if (rc) { 
            break;
        }
    }
    VERIFY_TEST(rc, "SEQUENTIAL ENQUEUE");


    for (i = 0; i < TEST_ELEMENTS; ++i) {  
        return_element = queue_dequeue(&test_queue, vm_offset);
        if (!return_element) {
            rc = 1;
            break;
        }
        
        if (return_element->item != i) {
            rc = 1;
            break;
        }
        
        free(return_element);
    }
    VERIFY_TEST(rc, "SEQUENTIAL DEQUEUE");
    

    for (i = 0; i < TEST_ELEMENTS; ++i) {
        new_element = calloc(1, sizeof(*new_element));
        if (!new_element) {
            fprintf(stderr, "[%s:%u]: calloc returned null.  OOM Error.\n",
                    DEBUG_INFO);
            rc = 1;
            break;
        }
        new_element->item = i;
        rc = queue_enqueue(&test_queue, new_element, vm_offset);
        if (rc) {
            free(new_element);
            break;
        }
        
        if (i % 7 == 5) {
            for (j = 0; j < 3; ++j) {
                return_element = queue_dequeue(&test_queue, vm_offset);
                printf("[%s:%u]: return_element->item: %d\n",
                        DEBUG_INFO, return_element->item);
                if (!return_element) {
                    rc = 1;
                    break;
                }

                if (return_element->item != last_dequeued) {
                    rc = 1;
                    free(return_element);
                    break;
                }
                last_dequeued++;
                free(return_element);
            }
        }
    }
    VERIFY_TEST(rc, "MIXED QUEUE OPS");

    int remaining_elements = queue_length(&test_queue);
    for (i = 0; i < remaining_elements; ++i) {
        return_element = queue_dequeue(&test_queue, vm_offset);
        if (!return_element) {
            rc = 1;
            break;
        }
        free(return_element); 
    }
    VERIFY_TEST(rc, "CLEANUP");

    return rc;
}



