/*
 * Test programs for doubly linked list.
 * Each node will hold int pointers.
 * Author: Cyrus Ramavarapu
 * Date: 14 July 17
 */

#include <stdlib.h>
#include <stdio.h>
#include "../doubly_linked_list.h"

/* Macro to announce if the test failed or passed */
#define VERIFY_TEST(x, name) {\
if (x == 1) {\
    printf("[FAILURE] %s\n", name);\
} else {\
    printf("[PASSED] %s\n", name);\
}\
}

/* Casts and dereferences a void pointer to an int */
#define VOID_TO_INT(void_ptr) *(int *)(void_ptr) 

/* Maximum length of the list for testing */
#define MAX_LIST_LENGTH 20

/* Using debugging output */
#define DEBUG 0

/*
 * Should return that an empty list has a 
 * length of 0.
 */
int empty_test(
        struct dbl_node *head)
{
    int length = get_length(head);

    if (length != 0) {
#if DEBUG
        printf("[Empty Test]: Empty list returned length %d\n",
                length);
#endif
        return 1;
    }

    return 0;
}

/*
 *  Should return 1 for a list with one element
 */
int single_test(
        struct dbl_node *head)
{
    int length = get_length(head);

    if (length != 1) {
#if DEBUG
        printf("Got length of %d\n", length);
#endif
        return 1;
    }
    
    return 0;
}

/*
 * Should append 1 node to the head of the list
 */
int append_test(
        struct dbl_node **head,
        int             *new_value)
{
    int org_head_value              = 0;
    int rc                          = 0;

    struct dbl_node *new_node                 = NULL; 

    org_head_value = VOID_TO_INT((*head)->value);

    rc = append(head, new_value);
    
    /* The append should succeed */
    if (rc != 0) {
#if DEBUG
        printf("[Append Test]: append failed with rc %d\n",
                rc);
#endif
        return 1;
    }
    
    /* The value in the head node should remain the same */
    if (VOID_TO_INT((*head)->value) != org_head_value) {
#if DEBUG
        printf("[Append Test]: head node value changed to %d\n",
                VOID_TO_INT((*head)->value));
#endif
        return 1;
    }
    
    /* The node to previous should still be null */
    if ((*head)->previous != NULL) {
#if DEBUG
        printf("[Append Test]: head->previous points to %p\n",
                (*head)->previous);
#endif
        return 1;
    }

    new_node = (*head)->next;

    /* The new node should not be NULL */
    if (new_node == NULL) {
#if DEBUG
        printf("[Append Test]: new node was NULL\n");
#endif
        return 1;
    }
    
    /* The new node should point to the previous.
     * The head node in this case.
     */
    if (new_node->previous != *head) {
#if DEBUG
        printf("[Append Test]: new_node->previous points to %p\n",
                new_node->previous);
#endif
        return 1;
    }
    
    /*
     * The new node should have the new value stored.
     */
    if (VOID_TO_INT(new_node->value) != *new_value) {
#if DEBUG
        printf("[Append Test]: new_node holds %d instead of %d\n",
                VOID_TO_INT(new_node->value), *new_value);
#endif
        return 1;
    }
    
    /*
     * The new node should point to NULL as next.
     */
    if (new_node->next != NULL) {
#if DEBUG
        printf("[Append Test]: new_node->next points %p\n",
                new_node->next);
#endif
        return 1;
    }

    return 0;
}

int get_test(
        struct dbl_node         *head,
        int                     current_length)
{
    
    int node_value                      = 0;
    int list_length                     = get_length(head);
    struct dbl_node *current_node       = NULL;
#if DEBUG
    int current_node_value              = 0;
#endif

    if (list_length != current_length) {
        return 1;
    }

#if DEBUG
    printf("[Get Test]: Passed length check\n");
#endif

    for (int i = 0; i < current_length; i++) {
        current_node = get(head, i);
#if DEBUG
        current_node_value = VOID_TO_INT(current_node->value);
        printf("[Get Test]: Node %d Value %d\n", i, current_node_value);
#endif
        if (node_value != VOID_TO_INT(current_node->value)) {
            return 1;
        }
        node_value++;
    }
    
    current_node = get(head, current_length + 1);

    if (current_node != NULL) {
#if DEBUG
        printf("[Get Test]: Current node contains value %d\n", 
                VOID_TO_INT(current_node->value));
#endif
    return 1;
    }
        
    return 0;
}

int get_last_test(
        struct dbl_node         *head,
        int                     last_value)
{
    struct dbl_node *last_node      = NULL;
    
    last_node = get_last(head);

    if (VOID_TO_INT(last_node->value) != last_value) {
#if DEBUG
        printf("[Last Test]: last node had %d instead of %d\n",
                VOID_TO_INT(last_node->value), last_value);
#endif
        return 1;
    }
    return 0;
}

int reverse_read_test(
        struct dbl_node         *head,
        int                     last_value)
{
    struct dbl_node *current_node      = NULL;
    
    for (current_node = get_last(head);
            current_node != NULL;
            current_node = current_node->previous) {
#if DEBUG
        printf("[Reverse Read Test]: Current Node has value %d\n",
                VOID_TO_INT(current_node->value));
#endif
        if (VOID_TO_INT(current_node->value) != last_value) {
#if DEBUG
            printf("[Reverse Read Test]: Node had value %d instead of %d\n",
                    VOID_TO_INT(current_node->value), last_value);
#endif 
            return 1;
        }
        last_value--;
    }

    return 0;
}

int free_list_test(
        struct dbl_node         *head)
{
#if DEBUG
    int loop_counter                    = 0;
#endif
    struct dbl_node *current_node       = NULL;
    struct dbl_node *next_node          = NULL;

    for (current_node = head;
            current_node != NULL;
            current_node = next_node) {
        next_node = current_node->next;
#if DEBUG
        printf("[Free List Test]: --------Iteration %d--------\n", 
                loop_counter);   
        printf("[Free List Test]: Current node: %p\nNext Node: %p\n",
                current_node, next_node);
        loop_counter++;
#endif
        free(current_node);
    }
    return 0;
}



/* Entry point for test suite */
int main()
{
    struct dbl_node *head       = NULL;
    int  head_value             = 0; 
    int rc                      = 0; 
    int new_value               = 0;
    int current_length          = 0;
    int list_values[MAX_LIST_LENGTH];

    /* Get length of an empty list */
    rc = empty_test(head); 
    VERIFY_TEST(rc, "empty_test");

    head = calloc(1, sizeof *head);
    head->next = NULL;
    head->previous = NULL;
    head->value = &head_value;
    
    rc = single_test(head);
    VERIFY_TEST(rc, "single_test");

    new_value = 1;
    rc = append_test(&head, &new_value); 
    VERIFY_TEST(rc, "append_test");
    /*
     * Append twenty (20) nodes to the
     * list and verify contents.
     */
    for (int i = 0; i < MAX_LIST_LENGTH; i++) {
        list_values[i] = i+2;
        /* Each node holds a pointer to 
         * an array element.
         */
        append(&head, list_values + i);
    }
    
    current_length = MAX_LIST_LENGTH + 2;
    rc = get_test(head, current_length);
    VERIFY_TEST(rc, "get_test"); 

    rc = get_last_test(head, 
                       list_values[MAX_LIST_LENGTH-1]);
    VERIFY_TEST(rc, "get_last_test");

    rc = reverse_read_test(head,
                           list_values[MAX_LIST_LENGTH-1]);
    VERIFY_TEST(rc, "reverse_read_test");

    rc = free_list_test(head);
    VERIFY_TEST(rc, "free_list_test");
    
    return 0;
}
