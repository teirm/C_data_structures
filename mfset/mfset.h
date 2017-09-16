/*
 * Purpose: A tree implementation with merge
 *          and find.  Uses path compression.
 * Author:  Cyrus Ramavarapu
 * Date:    16 September 17
 */

#include <stdlib.h>
#include <ds/debug.h>

#define MAX_CHILDREN 1024                       /* Upper bound for node children */

struct mfset {
    int                         (comp)(void *, void *);    /* Comparison function */      
    int                         *mfset_sizes;              /* Array of sizes */                         
    struct mfset_node           *mfset_roots;              /* Array of roots */
};

struct mfset_node {
    struct mfset_node       *parent;            /* Point to the nodes parent */
    struct mfset_node       *children;          /* Array of children */
    void                    *elem;              /* element held by node */
};

struct mfset_node*
mfset_find(
            struct mfset        *mfset_roots,
            void                *value);


struct mfset_node*
mfset_merge(
            struct mfset_node   *set_a,
            struct mfset_node   *set_b);


struct mfset *
mfset_initialize(
        int             (comp)(void *, void *));
