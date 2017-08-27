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
#define MAX_SIZE 10 

#define DEBUG 1

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
int 
comparator(
        const void            *a,
        const void            *b)
{
    
    if (*(int *)a > *(int *)b) {
#if DEBUG
        printf("[%s:%d] Returning 1: %d > %d\n",
                DEBUG_INFO, *(int *)a, *(int *)b);
#endif 
        return 1;
    } else if (*(int *)a < *(int *)b){
#if DEBUG
        printf("[%s:%d] Returning -1: %d < %d\n",
                DEBUG_INFO, *(int *)a, *(int *)b);
#endif
        return -1;
    } else {
#if DEBUG
        printf("[%s:%d] Returning 0: %d == %d\n",
                DEBUG_INFO, *(int *)a, *(int *)b);
#endif
        return 0;
    }
}


/* print out function for traversals */
void
print_node(
    struct bin_node             *node)
{
#if DEBUG
    printf("[%s:%d] Node %p contents:\n" \
           "\t\tLeft Child:  %p\n" \
           "\t\tRight Child: %p\n" \
           "\t\tValue:       %d\n",
                DEBUG_INFO, node, 
                node->left_child,
                node->right_child,
                NODE_TO_INT(node));
#endif
    printf("[%s:%d] Node %d\n" \
           "\t\tLeft Child: %d\n"\
           "\t\tRight Child: %d\n",
           DEBUG_INFO, NODE_TO_INT(node),
           node->left_child ? NODE_TO_INT(node->left_child): 0x0,
           node->right_child ? NODE_TO_INT(node->right_child): 0x0);
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
#if DEBUG
        printf("[%s:%d] ERROR: root == NULL\n",
                DEBUG_INFO);
#endif /* DEBUG */
        return 1;
    }

    if (root->left_child == NULL) {
#if DEBUG
        printf("[%s:%d] ERROR: root->left_child == NULL\n",
                DEBUG_INFO);
#endif /* DEBUG */
        return 1;
    }

    if (root->right_child == NULL) {
#if DEBUG
        printf("[%s:%d] ERROR: root->right_child == NULL\n",
                DEBUG_INFO);
#endif /* DEBUG */
        return 1;
    }
    
    return 0;
}


/*
 * Execute a preorder traversal. 
 */
int
preorder_test_one(
        struct bin_node         *root)
{
    int rc      = 0;
    rc = preorder_traversal(root, print_node);
    return rc;
}

/*
 * Execute a postorder traversal.
 */
int
postorder_test_one(
        struct bin_node         *root)
{
    postorder_traversal(root, print_node);
    return 0;
}

/*
 * Execute an inorder traversal.
 */
int
inorder_test_one(
        struct bin_node         *root)
{
    inorder_traversal(root, print_node);
    return 0;
}

int
complete_tree_test(
        struct bin_node         *root,
        int                     *int_array,
        int                     array_items)
{
    int i                       = 0;
    int rc                      = 0;
    struct bin_node *new_node   = NULL;
     

    
    for (i = 0; i < array_items; ++i) { 
        new_node = calloc(1, sizeof *new_node);
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        new_node->value = int_array + i;
        
        rc = create_node(root, new_node,
                         comparator);
#if DEBUG
        printf("[%s:%d] Create node return code: %d\n",
                DEBUG_INFO, rc);
#endif
        if (rc) {
            if (rc == DUPLICATE_ERROR) {
#if DEBUG
                printf("[%s:%d] Deleting duplicate node with value %d\n",
                DEBUG_INFO, int_array[i]);
#endif
            free(new_node);
            } else {
#if DEBUG
                printf("[%s:%d] Non-duplicate failure %d\n",
                        DEBUG_INFO, int_array[i]);
#endif
                return rc;
            }
        }
    }

    return 0;
}

int
delete_min_test(
        struct bin_node         *root,
        int                     min)
{
    struct bin_node *min_node   = NULL;

    min_node = delete_min(root);
    
    if (root == NULL) {
#if DEBUG
    printf("[%s:%d] ERROR: root == NULL\n",
            DEBUG_INFO);
#endif  /* DEBUG */
        return 1;
    }
    
    if (min_node == NULL) {
#if DEBUG
    printf("[%s:%d] ERROR: min_node == NULL\n",
            DEBUG_INFO);
#endif  /* DEBUG */
        return 1;
    }

    if (NODE_TO_INT(min_node) != min) {
#if DEBUG
    printf("[%s:%d] ERROR: Not Min %d. Node value: %d\n",
            DEBUG_INFO, min, NODE_TO_INT(min_node));
#endif  /* DEBUG */
        return 1;
    }

    free(min_node);

    return 0;
}

int
delete_existant_test(
        struct bin_node         *root,
        int                     value)
{
    struct bin_node *deleted_node    = NULL;
    
    deleted_node = delete_node(root, &value, comparator);

    if (root == NULL) {
#if DEBUG
        printf("[%s:%d] ERROR: root == NULL\n",
                DEBUG_INFO);
#endif /* DEBUG */
        return 1;
    }

    if (deleted_node == NULL) {
#if DEBUG
        printf("[%s:%d] ERROR: deleted_node == NULL\n",
                DEBUG_INFO);
#endif /* DEBUG */
        return 1;
    }

    if (NODE_TO_INT(deleted_node) != value) {
#if DEBUG
        printf("[%s:%d] ERROR: deleted_node (%d) != value (%d)\n",
                DEBUG_INFO, NODE_TO_INT(deleted_node), value);
#endif /* DEBUG */
        return 1;
    }

    printf("VALUE OF DELETED NODE: %d\n", NODE_TO_INT(deleted_node)); 

    free(deleted_node);

    return 0;
}

int
delete_nonexistant_test(
        struct bin_node         *root,
        int                     value)
{
    struct bin_node *deleted_node   = NULL;

    deleted_node = delete_node(root, &value, comparator);

    if (deleted_node != NULL) {
        return 1;
    }

    return 0;
}


/* Clean up function for clean up test */
void
free_node(
        struct bin_node         *node)
{
    free(node);
}


int
clean_up_test(
        struct bin_node         *root)
{
    postorder_traversal(root, print_node);
    return 0;
}

/* Main entry point for tests. */
int main()
{
    int i                       = 0; 
    int rc                      = 0; 
    int min                     = MAX_VALUE; 
    int int_array[MAX_SIZE];
        
    struct bin_node *root       = NULL;
    

    for (i = 0; i < MAX_SIZE; i++) {
        int_array[i] = rand() % MAX_VALUE;
        min = int_array[i] < min ? int_array[i] : min;
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

    rc = complete_tree_test(root, int_array+3, MAX_SIZE-3);
    VERIFY_TEST(rc, "complete_tree_test");

    rc = preorder_test_one(root);
    VERIFY_TEST(rc, "preorder_test_one");
    
    rc = postorder_test_one(root);
    VERIFY_TEST(rc, "post_test_one");
    
    rc = inorder_test_one(root);
    VERIFY_TEST(rc, "inorder_test_one");

    rc = delete_min_test(root, min);
    VERIFY_TEST(rc, "delete_min_test");
    
    rc = inorder_test_one(root);
    VERIFY_TEST(rc, "inorder_test_one");

    rc = delete_existant_test(root, int_array[5]);
    VERIFY_TEST(rc, "delete_existant_test");

    /* Test bin tree does not have negative values */
 //   rc = delete_nonexistant_test(root, -99);
    VERIFY_TEST(rc, "delete_nonexistant_test");

  //  rc = clean_up_test(root);
    VERIFY_TEST(rc, "clean_up_test");
    
    return 0;
}
