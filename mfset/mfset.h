/*
 * Purpose: A tree implementation with merge
 *          and find.  Uses path compression.
 *          Note: Equivalence classes  will be 
 *                identified by the root. 
 * Author:  Cyrus Ramavarapu
 * Date:    16 September 17
 */

#include <stdlib.h>
#include <ds/debug.h>

#define MAX_CHILDREN 1024                       /* Upper bound for node children */

struct mfset {
    int                         (*comp)(void *, void *);    /* Comparison function */
    int                         *mfset_sizes;              /* Array of sizes */                         
    struct mfset_node          **mfset_roots;              /* Array of roots */
};

struct mfset_node {
    int                         position;           /* Position in the array of roots */
    int                         next_child; 
    struct mfset_node           *parent;            /* Point to the nodes parent */
    struct mfset_node          **children;          /* Array of children */
    void                        *elem;              /* element held by node */
};

struct mfset_node*
mfset_find(
    struct mfset_node       *elem);

int
mfset_merge(
    struct mfset            *set,
    struct mfset_node       *elem_a,
    struct mfset_node       *elem_b);

int
mfset_do_merge(
    struct mfset_node       *smaller,
    struct mfset_node       *larger);


struct mfset *
mfset_initialize(
        int             initial_size,
        int             (*comp)(void *, void *));

int 
mfset_compress_path(
    struct mfset_node       *root,
    struct mfset_node       *elem);

int mfset_remove_child(
    struct mfset_node       *parent,
    struct mfset_node       *child);



