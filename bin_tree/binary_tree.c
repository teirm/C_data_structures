/*
 * Author: Cyrus Ramavarapu
 * Date: 16 July 2017
 * Purpose: Binary tree implementation.
 */

#define DEBUG 0

#include <stdlib.h>


#if DEBUG
#include <stdio.h>
#define DEBUG_INFO __FUNCTION__, __LINE__
#endif

#include "binary_tree.h"



int create_node(
        struct bin_node         *root,
        struct bin_node         *new_node,
        int (*comp)(const void *a, const void *b))
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

struct bin_node*
delete_node(
    struct bin_node             *root,
    void                        *value,
    int (*comp)(const void *a, const void *b))
{
    int direction               = 0;
    struct bin_node *parent     = NULL;
    struct bin_node *to_delete  = NULL;
    struct bin_node *right_min  = NULL;

    to_delete = root;
    
    do {
        if (comp(to_delete->value, value) == 0) {
            break;
        } else if (comp(to_delete->value, value)  > 0) {
            parent = to_delete;
            to_delete = to_delete->left_child;
            direction = -11;
        } else { 
            parent = to_delete;
            to_delete = to_delete->right_child;
            direction = 1;
        }
    } while (to_delete != NULL);


    if (to_delete != NULL && parent == NULL) {
        /* Deleting root case */
        right_min = delete_min(to_delete->right_child);
        if (right_min == NULL) {
            root = to_delete->left_child;
            to_delete->left_child = NULL;
        } else {
            right_min->left_child = to_delete->left_child;
            right_min->right_child = to_delete->right_child;
            
            to_delete->left_child = NULL;
            to_delete->right_child = NULL;

            if (direction > 0) {
                parent->right_child = right_min;
            } else {
                parent->left_child = right_min;
            }
        }
    } else if (to_delete != NULL && parent != NULL) {
        right_min = delete_min(to_delete->right_child);

        if (right_min == NULL) {
            if (direction > 0) {
                parent->right_child = to_delete->left_child;
            } else {
                parent->left_child = to_delete->left_child;
            }
        } else {
            right_min->left_child = to_delete->left_child;
            
            if (right_min != to_delete->right_child) { 
                right_min->right_child = to_delete->right_child;
            }

            to_delete->left_child = NULL;
            to_delete->right_child =NULL;

            if (direction > 0) {
                parent->right_child = right_min;
            } else {
                parent->left_child = right_min;
            }
        }
    } else {
#if DEBUG
        fprintf(stderr, "[%s:%d] Value: %p not found in tree\n",
                DEBUG_INFO, value);
#endif
    }
    
    return to_delete;
}


struct bin_node*
delete_min(
    struct bin_node             *root)
{
    struct bin_node *g_parent   = NULL; 
    struct bin_node *parent     = NULL;
    struct bin_node *child      = NULL;
    

    parent = root;
   
    if (parent == NULL) {
        return NULL;
    }
     
    child = parent->left_child;

    while (child != NULL){
        g_parent = parent;
        parent = child;
        child = parent->left_child;
    }

    if (g_parent) {
        g_parent->left_child = parent->right_child;
    } 
    parent->right_child = NULL;
    return parent;
}


struct bin_node*
find_node(
    struct bin_node             *root,
    void                        *value,
    int (*comp)(void *a, void *b))
{
    
    if (root == NULL) {
        return root;
    } else if (comp(root->value, value) == 0) {
        return root;
    } else if (comp(root->value, value) < 0) {
        return find_node(root->left_child, value, comp);
    } else {
        return find_node(root->right_child, value, comp);
    }
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

