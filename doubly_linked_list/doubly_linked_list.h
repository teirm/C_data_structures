/*
 * Author: Cyrus Ramavarapu
 * Date: 13 July 2017
 * Purpose: Doubly Linked List Prototypes
 */

#ifndef DOUBLY_LINKED_LIST_GUARD
#define DOUBLY_LINKED_LIST_GUARD

#include <stdlib.h>


struct dbl_node {
    struct dbl_node     *previous;
    struct dbl_node     *next;
    void                *value;
};

/*
 * Appends a node containing value to the 
 * doubly linked list.
 */
int append(struct dbl_node **head, void *value);

/*
 * Gets the last node in the doubly linked list.
 */
struct dbl_node *get_last(struct dbl_node *head);

/*
 * Inserts a node with value at the given position.
 */
int insert(struct dbl_node **head, void *value, int position);

/*
 * Gets the node at the given position.
 */
struct dbl_node *get(struct dbl_node *head, int position);

/*
 * Gets the length of the doubly linked list.
 */
int get_length(struct dbl_node *head);

#endif
