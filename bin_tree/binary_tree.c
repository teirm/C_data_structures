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
    int rc                  = 0;
    comp_result = comp(root->value, new_node->value);

    if (comp_result < 0) {
        if (root->right_child == NULL) {
            root->right_child = new_node;
        } else {
            rc = create_node(root->right_child, new_node, comp);
        }
    } else if (comp_result > 0) {
#if DEBUG
        printf("[%s:%d] Taking left_branch.\n",
                __FUNCTION__, __LINE__);
#endif
        if (root->left_child == NULL) {
#if DEBUG
        printf("[%s:%d] adding node %p to root %p\n",
                DEBUG_INFO,
                new_node, root);
#endif 
            root->left_child = new_node;
        } else {
            rc = create_node(root->left_child, new_node, comp);
        }
    } else {
#if DEBUG
        printf("[%s:%d] Duplicate value found.\n",
                DEBUG_INFO);
#endif 
        return DUPLICATE_ERROR;
    }
    return rc;
}

/* 
 * TODO: Delete node -- I think it is a 
 * float down procedure.
 */
int delete_node()
{
#if DEBUG
    fprintf(stderr, "[%s:%d] ERROR: %s not implemented\n",
            DEBUG_INFO, __FUNCTION__);
#endif
    return 0;
}


int preorder_traversal(
        struct bin_node         *node,
        void (*node_op)(struct bin_node *a))
{
    if (node == NULL) {
        return 0;
    }
    node_op(node);
    preorder_traversal(node->left_child, node_op);
    preorder_traversal(node->right_child, node_op);
    return 0;
}  

int postorder_traversal(
        struct bin_node         *node,
        void (*node_op)(struct bin_node *a))
{
    if (node == NULL) {
        return 0;
    }
    postorder_traversal(node->left_child, node_op);
    postorder_traversal(node->right_child, node_op);
    node_op(node);
    return 0;
}

int inorder_traversal(
        struct bin_node         *node,
        void (*node_op)(struct bin_node *a))
{
    if (node == NULL) {
        return 0;
    }
    inorder_traversal(node->left_child, node_op);
    node_op(node);
    inorder_traversal(node->right_child, node_op);
    return 0;
}

