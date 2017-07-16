/*
 * Author: Cyrus Ramavarapu
 * Date: 16 July 2017
 * Purpose: Binary Search Tree prototypes
 */

#ifndef BINARY_TREE_GUARD
#define BINARY_TREE_GUARD

struct bin_node {
    struct bin_node     *left_child;
    struct bin_node     *right_child;
    void                *value;
};

/*
 * Create a node and insert it into the
 * tree at first available position.
 */
int create_node(struct bin_node *root, struct bin_node *new_node,
                int (*comp)(void *a, void *b));

/*
 * Delete a node from the tree. Left child, if available
 * becomes parent.  Otherwise right child.
 */
int delete_node(struct bin_node *root, struct bin_node *node,
                int (*comp)(void *a, void *b));

/*
 * Preorder traversal of tree.
 */
int preorder_traversal(struct bin_node *root);

/*
 * Postorder traversal of tree.
 */
int postorder_traversal(struct bin_node *root);

/*
 * Inorder traversal of tree.
 */
int inorder_traversal(struct bin_node *root);

#endif
