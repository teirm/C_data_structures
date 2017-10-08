/* Purpose: Implementation of merge find
 *          set.
 * Author:  Cyrus Ramavarapu
 * Date:    24 September 2017
 */

#include "mfset.h"


struct mfset*
mfset_initialize(
    int                         initial_size,
    int                         (*comp)(void *, void *))
{
    struct mfset                *set = NULL;
    
    set = calloc(1, sizeof *set);

    if (set == NULL) {
        return NULL;
    }
   
    set->mfset_roots = calloc(initial_size,
                                    sizeof *(set->mfset_roots));

    /* QUESTION: can a compiler optimize these into a rollback structure
     *           instead of a single branch prediction?
     */
    if (set->mfset_roots == NULL) {
        free(set);
        return NULL;
    }
    
    set->mfset_sizes = calloc(initial_size,
                                    sizeof *(set->mfset_roots));
    
    if (set->mfset_sizes == NULL) {
        free(set->mfset_roots);
        free(set);
        return NULL;
    }

    set->comp = comp;

    return set;
}

int
mfset_merge(
        struct mfset            *set,
        struct mfset_node       *elem_a,
        struct mfset_node       *elem_b)
{
    int                         rc         = 0; 
    int                         set_a_size = 0;
    int                         set_b_size = 0;
    int                         total_size = 0;
    struct mfset_node           *elem_a_root = elem_a;
    struct mfset_node           *elem_b_root = elem_b;

    elem_a_root = mfset_find(elem_a_root);
    elem_b_root = mfset_find(elem_b_root);

    set_a_size = set->mfset_sizes[elem_a_root->position];
    set_b_size = set->mfset_sizes[elem_b_root->position]; 
    total_size = set_a_size + set_b_size; 

    if (set_a_size > set_b_size) {
        rc = mfset_do_merge(elem_a_root, elem_b_root);
        if (rc) {
            return rc;
        }
        set->mfset_sizes[elem_a_root->position] = total_size;
        /* Set has moved, so root no longer should point to anything */
        set->mfset_roots[elem_b_root->position] = NULL ; 
    } else {
        rc = mfset_do_merge(elem_b_root, elem_a_root);
        if (rc) {
            return rc;
        }
        set->mfset_sizes[elem_b_root->position] = total_size;
        /* Set has moved, so root no longer should point to anything */
        set->mfset_roots[elem_a_root->position] = NULL; 
    }
    return rc; 
}


int
mfset_do_merge(
    struct mfset_node           *smaller,
    struct mfset_node           *larger)
{
    int                         rc = 0;                       
    int                         next_child = larger->next_child; 

    if (next_child == MAX_CHILDREN) {
        return DS_ECAP;
    }
    larger->children[next_child++] = smaller;

    return rc;
}

struct mfset_node*
mfset_find(
    struct mfset_node           *elem)
{
    int                         rc = 0;                      
    struct mfset_node           *elem_root = elem;

    while (elem_root->parent) {
        elem_root = elem_root->parent;
    }

    rc = mfset_compress_path(elem_root, elem); 
    if (rc) {
        return NULL;
    }

    return elem_root;
}

int
mfset_compress_path(
    struct mfset_node           *root,
    struct mfset_node           *elem)
{
    int rc                      = 0;
    struct mfset_node           *curr_elem = elem;
    struct mfset_node           *parent = curr_elem->parent;

    if (parent == NULL) {
        goto exit;
    }

    while (parent != root) {
        rc = mfset_remove_child(parent, elem);
        if (rc) {
            goto exit;
        }
        rc = mfset_do_merge(curr_elem, root);
        if (rc) {
            goto exit;
        }
        curr_elem = parent;
        parent = curr_elem->parent;
    }
exit:    
    return 0;
}

int
mfset_remove_child(
    struct mfset_node           *parent,
    struct mfset_node           *del_child)
{
    int                          child_pos = 0;
    int                          last_child = parent->next_child - 1;
    struct mfset_node           *current_child = parent->children[0];    
    
    /* Is the array of children calloc'd to NULLs? */
    while (current_child != NULL) {
        if (current_child == del_child) {                     
            break;
        }
        child_pos++; 
    }    
    
    if (current_child == NULL) {
        return DS_ENOTFOUND;
    }
    
    /* There is no need to keep the children of a node
     * in order since this is a set.
     */
    parent->children[child_pos] = parent->children[last_child];
    parent->next_child--;
    
    return 0;
}




