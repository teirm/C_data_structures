/* 
 * Purpose: Implementation of the priority 
 *          Queue.
 *
 * Author: Cyrus Ramavarapu
 * Date: 24 July 2017
 */


#include <stdlib.h>
#include <ds/debug.h>

#include "priority_queue.h"

struct priority_node *
delete_min(
        struct priority_queue       *pq)
{
    struct priority_node *old_root      = pq->root;        
    struct priority_node *new_root      = pq->next_delete;
    struct priority_node *old_parent    = new_root->parent;
    

    if (old_parent->left_child == new_root) {
        old_parent->left_child = NULL;
    } else {
        old_parent->right_child = NULL;
    }

    new_root->left_child = old_root->left_child;
    new_root->right_child = old_root->right_child;
    
    old_root->left_child = NULL;
    old_root->right_child = NULL;

    pq->root = new_root;
    
    /* Float new root value down */

    return old_root;
}


struct priority_node *
right_most_null(
        struct priority_node        *pn)
{
    struct priority_node *next_parent = NULL; 
    

}


int
insert(
        struct priority_queue       *pq,
        struct priority_node        *pn)
{
    return 0;
}


int
delete_tree(
        struct priority_queue       *pq)
{
    return 0;
}

