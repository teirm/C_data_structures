/*
 * Author: Cyrus Ramavarapu
 * Date: 16 July 2017
 * Purpose: Binary tree implementation.
 */

#define DEBUG 0

#include <stdlib.h>

#if DEBUG
#include <stdio.h>
#endif

#include "binary_tree.h"

#define DEBUG_INFO __FUNCTION__, __LINE__

int create_node(
        struct bin_node         *root,
        struct bin_node         *new_node,
        int (*comp)(void *a, void *b))
{
    int comp_result         = 0;
    comp_result = comp(root->value, new_node->value);

    if (comp_result <= 0) {
        if (root->right_child == NULL) {
            root->right_child = new_node;
        } else {
            create_node(root->right_child, new_node, comp);
        }
    } else {
#if DEBUG
        printf("[%s:%d] Taking left_branch.\n",
                __FUNCTION__, __LINE__);
#endif
        if (root->left_child == NULL) {
#if DEBUG
        printf("[%s:%d] adding node %p to root %p\n",
                __FUNCTION__, __LINE__,
                new_node, root);
#endif 
            root->left_child = new_node;
        } else {
            create_node(root->left_child, new_node, comp);
        }
    }
    return 0;
}
