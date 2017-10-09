/* Purpose: Test suite for mfset
 * Author:  Cyrus Ramavarapu
 * Date:    07 October 2017
 */

#include <stdlib.h>
#include <stdio.h>

#include <ds/debug.h>

#include "../mfset.h"

#define TEST_ELEMENTS 10
#define MAX_ELEMENT   1000

int element_array[TEST_ELEMENTS];

int
cleanup(
    struct mfset        *test_set,
    struct mfset_node   **node_array)
{
    int i;
    int curr_child               = 0;
    struct mfset_node *curr_node = NULL;

    for (i = 0; i < TEST_ELEMENTS; i++) {
        curr_node = node_array[i];
        curr_child = curr_node->next_child - 1; /* next child points to the next empty location */ 
        while (curr_child) {
            free(curr_node->children[curr_child--]);
        }
        free(curr_node->children);
        free(curr_node);
    }
    
    free(node_array);
    free(test_set->mfset_roots);
    free(test_set->mfset_sizes);
    free(test_set);

    return 0;
}

int
create_set(
    struct mfset_node   **node_array)
{
    int i = 0;

    for (i = 0; i < TEST_ELEMENTS; i++) {
        node_array[i] = calloc(1, sizeof **node_array);
        node_array[i]->position = i;
        node_array[i]->next_child = 0;
        node_array[i]->parent = NULL;
        node_array[i]->children = calloc(MAX_CHILDREN, sizeof *(node_array[i]->children));
        
        if (!node_array[i]->children) {
            return DS_ENOMEM;
        }
        node_array[i]->elem = &element_array[i]; 
    }

    return 0;
}

int
check_sanity(
    struct mfset        *test_set)
{   
    int i;

    if (!test_set) { return 1; }
    if (!test_set->mfset_sizes) { return 1; }
    if (!test_set->mfset_roots) { return 1; }
    if (!test_set->comp) { return 1; }


    for (i = 0; i < TEST_ELEMENTS; i++) {
        if (test_set->mfset_sizes[i] != 1) { return 1; }
        if (!test_set->mfset_roots[i]) { return 1; }
        if (!test_set->mfset_roots[i]->children) { return 1; }
        if (!test_set->mfset_roots[i]->elem) { return 1; }
    }

    return 0;
}

int
mfset_int_comp(
    void            *a,
    void            *b)
{
    if (*(int *)a > *(int *)b) {
        return 1;
    } else if (*(int *)a < *(int *)b) {
        return -1;
    } else {
        return 0;
    }
}

int
test_basic_merge(
    struct mfset             *test_set,
    struct mfset_node        **node_array)
{
    /* Merging 0 and 3 since they are same on Z/3Z */
    return mfset_merge(test_set, node_array[0], node_array[3]);
}

int 
test_large_merge(
    struct mfset            *test_set,
    struct mfset_node       **node_array)
{
    return mfset_merge(test_set, node_array[3], node_array[6]);
}


int
test_find(
    struct mfset_node       **node_array)
{
    return mfset_find(node_array[3]) ?  0 : 1;
}

int
test_nonexistant()
{
    int invalid_entry = 30;
    struct mfset_node invalid_node;

    invalid_node.position = 20;
    invalid_node.next_child = 2;
    invalid_node.parent = NULL;
    invalid_node.children = NULL;
    invalid_node.elem = &invalid_entry;

    if (mfset_find(&invalid_node)) {
        return 1;
    }

    return 0;
}

            

/*
 * Test mfset via equalivalence set creation.
 * Since the numbers are small this example 
 * will be of the 0s in Z/3Z.
 */
int main()
{
    int i                                   = 0;
    int rc                                  = 0;
    struct mfset *test_set                  = NULL; 
    struct mfset_node **node_array          = NULL;

    
    /* Elements are set to simple numbers for test
     * purpose.
     */
    for (i = 0; i < TEST_ELEMENTS; i++) {
        element_array[i] = i;
    }
   
    /* Initialization for test_set */
    test_set = calloc(1, sizeof *test_set);
    test_set->mfset_sizes = calloc(TEST_ELEMENTS, sizeof *test_set->mfset_sizes);
    test_set->mfset_roots = calloc(TEST_ELEMENTS, sizeof *test_set->mfset_roots);
    test_set->comp = mfset_int_comp; 

    /* Initialization for the disorganized set of elements */
    node_array = calloc(TEST_ELEMENTS, sizeof *node_array);
    rc = create_set(node_array);
    VERIFY_TEST(rc, "create_set");  

    for (i = 0; i < TEST_ELEMENTS; i++) { 
        test_set->mfset_roots[i] = node_array[i];
        test_set->mfset_sizes[i] = 1;
    }
    /* Check setup prior to testing */
    rc = check_sanity(test_set);
    VERIFY_TEST(rc, "check_sanity");

    /*
     * Tests to perform:
     *
     * Basic merge (1 into 1)
     * Large merge (m into n where n > m)
     * Find and path compression
     * Find non existent element
     */

    rc = test_basic_merge(test_set, node_array);
    VERIFY_TEST(rc, "test_basic_merge");

    rc = test_large_merge(test_set, node_array);
    VERIFY_TEST(rc, "test_large_merges");
/*
    rc = test_find(node_array);
    VERIFY_TEST(rc, "test_find");

    rc = test_nonexistant();
    VERIFY_TEST(rc, "test_nonexistant");

    rc = cleanup(test_set, node_array);
    VERIFY_TEST(rc, "cleanup");
*/
    return rc;
}

