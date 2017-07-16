/*
 * Author: Cyrus
 * Date: 16-07-17
 * Purpose: Test suite for binary search tree holding 
 *          ints.
 */

#include <stdlib.h>
#include <stdio.h>

#include "../binary_tree.h"

#define MAX_VALUE 100
#define MAX_SIZE  20

#define DEBUG 0

#define VERIFY_TEST(x, name) {\
if (x == 1) {\
    printf("[FAILURE] %s\n", name);\
} else {\
    printf("[PASSED] %s\n", name);\
}\
}

#define DEBUG_INFO __FUNCTION__, __LINE__

/* Macro to get int value from node */
#define NODE_TO_INT(x) *(int *)(x->value)

/* Comparator function for ints */
int comparator(
        void            *a,
        void            *b)
{
    
    if (*(int *)a > *(int *)b) {
#if DEBUG
        printf("[%s:%d] Returning 1\n",
                DEBUG_INFO);
#endif 
        return 1;
    } else {
#if DEBUG
        printf("[%s:%d] Returning 0\n",
                DEBUG_INFO);
#endif
        return 0;
    }

}

int create_test(
        struct bin_node         *root,
        int                     *new_value)
{
    struct bin_node *new_node   = NULL;
    struct bin_node *added_node = NULL;

#if DEBUG
    printf("[%s:%d] Root node value: %d\n",
           DEBUG_INFO, NODE_TO_INT(root));
    printf("[%s:%d] Left Child: %p\nRight Child: %p\n",
            DEBUG_INFO, root->left_child, root->right_child);
#endif
    new_node = calloc(1, sizeof new_node);
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->value = new_value;

#if DEBUG
    printf("[%s:%d] Addres of new node: %p\n",
            DEBUG_INFO, new_node);
#endif
    create_node(root, new_node, &comparator); 

    if (root->left_child == NULL) {
        added_node = root->right_child;
#if DEBUG
        printf("[%s:%d]: Noded added to right: %d\n",
                DEBUG_INFO, NODE_TO_INT(added_node));
#endif
    } else if (root->right_child == NULL) {
        added_node = root->left_child;
#if DEBUG
        printf("[%s:%d]: Noded added to left: %d\n",
                DEBUG_INFO, NODE_TO_INT(added_node));
#endif
    } else {
#if DEBUG
        printf("[%s:%d]: Node failed to add\n",
                DEBUG_INFO);
#endif
        return 1;
    }

    return 0;
}

int create_again_test(
        struct bin_node         *root,
        int                     *new_value)
{
    create_test(root, new_value);
   
    if (root == NULL) {
        return 1;
    }

    if (root->left_child == NULL) {
        return 1;
    }

    if (root->right_child == NULL) {
        return 1;
    }

    return 0;
}

/* Main entry point for tests. */
int main()
{
    int i                       = 0; 
    int rc                      = 0; 
    int int_array[MAX_SIZE];
    
    struct bin_node *root       = NULL;
    

    for (i = 0; i < MAX_SIZE; i++) {
        int_array[i] = rand() % MAX_VALUE;
#if DEBUG
        printf("int_array[%d] = %d\n", i, int_array[i]);
#endif
    }

    root = calloc(1, sizeof *root);
    root->left_child = NULL;
    root->right_child = NULL;
    root->value = int_array; 
#if DEBUG
    printf("[%s:%d] Address of root: %p\n",
            DEBUG_INFO, root);
#endif

    rc = create_test(root, int_array+1);
    VERIFY_TEST(rc, "create_test");
    
    rc = create_again_test(root, int_array+2);
    VERIFY_TEST(rc, "create_again_test");

}
