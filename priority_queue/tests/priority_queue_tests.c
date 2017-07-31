/*
 * Purpose: Test Suite for Priority Queue.
 * Author:  Cyrus Ramavarapu
 * Date:    29 July 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <ds/debug.h>

#include "../priority_queue.h"

#define DEBUG 1
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

int
test_single_insert(
        struct priority_queue       *pq,
        struct priority_node        *pn)
{
    int rc                          = 0;
    struct priority_node *new_node  = NULL; 

    rc = insert(pq, pn);

    if (rc) {
        /* Insert failed */
        return rc;
    }
   
    if (pq->last_node != 1) {
        return 1;
    }

    new_node = pq->root[0];

    if (new_node->priority != pn->priority) {
        /* Priorities do not match */
#if DEBUG
        printf("[%s:%d] new_priority: %d\narg_priority: %d\n",
                DEBUG_INFO, new_node->priority, pn->priority);
#endif
        return 1;
    }

    if (VOID_TO_INT(new_node->value) != 
            VOID_TO_INT(pn->value)) {
        /* values do not match */
#if DEBUG
        printf("[%s:%d] new_value: %d\narg_value: %d\n",
                DEBUG_INFO, VOID_TO_INT(new_node->value),
                VOID_TO_INT(pn->value));
#endif
        return 1;
    }
    
    return 0;    
}

int
test_second_insert(
        struct priority_queue           *pq,
        struct priority_node            *pn_1,
        struct priority_node            *pn_2)
{
    int rc                              = 0;
    struct priority_node *check         = NULL;

    rc = insert(pq, pn_2);
    
    if (rc) {
        /* Insert 2 failed */
        return rc;
    }
    
    if (pq->last_node != 2) {
        return 1;
    }

    check = pq->root[0];

    if (pn_1->priority < pn_2->priority) {
        if (check->priority != pn_1->priority) {
            return 1;
        }

        if (VOID_TO_INT(check->value) != VOID_TO_INT(pn_1->value)) {
            return 1;
        }

        check = pq->root[1];

        if (check->priority != pn_2->priority) {
            return 1;
        }

        if (VOID_TO_INT(check->value) != VOID_TO_INT(pn_2->value)) {
            return 1;
        }

    } else {
        if (check->priority != pn_2->priority) {
            return 1;
        }

        if (VOID_TO_INT(check->value) != VOID_TO_INT(pn_2->value)) {
            return 1;
        }

        check = pq->root[1];

        if (check->priority != pn_1->priority) {
            return 1;
        }

        if (VOID_TO_INT(check->value) != VOID_TO_INT(pn_1->value)) {
            return 1;
        }
    }
    return rc;
}

int
test_full_insert(
        struct priority_queue           *pq,
        struct priority_node            **test_list,
        int                             list_size)
{
    int i;                                
    int rc                              = 0;

    for (i = 2; i < list_size; ++i) {
        rc = insert(pq, test_list[i]);
        if (rc) {
#if DEBUG
            printf("[%s:%d] Failed to insert node: %p at %d\n" \
                    "\tPriority: %d\n"\
                    "\tValue: %d\n",
                    DEBUG_INFO, test_list[i], i,
                    test_list[i]->priority,
                    VOID_TO_INT(test_list[i]->value));
#endif
            return 1;
        }
    }

    if (pq->last_node != list_size) {
        return 1;
    }

#if DEBUG
    for (i = 0; i < pq->last_node; ++i) {
        printf("[%s:%d] priority_node %d:\n\tpriority: %d\n\tvalue: %d\n",
                DEBUG_INFO, i, pq->root[i]->priority, 
                VOID_TO_INT(pq->root[i]->value));
    }
#endif

    return 0;
}


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

    rc = test_empty_delete(pq);
    VERIFY_TEST(rc, "test_empty_delete");
    
    rc = test_single_insert(pq, test_list[0]);  
    VERIFY_TEST(rc, "test_single_insert"); 

    rc = test_second_insert(pq, test_list[0], test_list[1]);
    VERIFY_TEST(rc, "test_second_insert");

    rc = test_full_insert(pq, test_list, INITIAL_QUEUE);
    VERIFY_TEST(rc, "test_full_insert");


    return 0;
}
