/*
 * Purpose: Test Suite for Priority Queue.
 * Author:  Cyrus Ramavarapu
 * Date:    29 July 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <ds/debug.h>

#include "../priority_queue.h"

#define DEBUG 0
#define VOID_TO_INT(x) *(int *)(x)
#define INITIAL_QUEUE 10
#define MAX_VALUE 100
#define MAX_PRIORITY 30

int
test_empty_delete(
        struct priority_queue       *pq)
{

    struct priority_node *rc = delete_min(pq);

    if (rc == NULL) {
        return 0;
    } else {
        return 1;
    }
}

/*int
test_single_insert(
        struct priority_queue       *pq)
{
}
*/
/* Main entry point to the test suite */
int main()
{
    int i;
    int rc                              = 0;
    int test_values[2 * INITIAL_QUEUE];
    struct priority_queue *pq           = NULL;
    struct priority_node *pn            = NULL;
    struct priority_node **test_list    = NULL;

    
    /* Create Queue and Initial Value */
#if DEBUG
    printf("[%s:%d] Initializing tests nodes\n",
            DEBUG_INFO);
#endif
    pq = calloc(1, sizeof *pq);
    pq->size = INITIAL_QUEUE;
    pq->last_node = 0;
    pq->root = calloc(pq->size, sizeof *(pq->root));

    /* Create test nodes */
    test_list = calloc(INITIAL_QUEUE, sizeof *test_list);

    for (i = 0; i < 2 * INITIAL_QUEUE; ++i) {
        test_values[i] = rand() % MAX_VALUE;
    }

    for (i = 0; i < INITIAL_QUEUE; ++i) {
        pn = calloc(1, sizeof *pn);
        pn->priority = rand() % MAX_PRIORITY;
        pn->value = test_values + i;
        test_list[i] = pn;
    }
    
#if DEBUG
    for (i = 0; i < INITIAL_QUEUE; ++i) {
        printf("[%s:%d] priority_node:\n\tpriority: %d\n\tvalue: %d\n",
                DEBUG_INFO, test_list[i]->priority, 
                VOID_TO_INT(test_list[i]->value));
    }
#endif

    printf("[%s:%d] pq->root[0]: %p\n",
            DEBUG_INFO, pq->root[0]);

    rc = test_empty_delete(pq);
    VERIFY_TEST(rc, "temp_empty_delete");
    
    //rc = test_single_insert(pq);  

    return 0;
}
