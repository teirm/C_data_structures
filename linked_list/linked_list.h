/*Author: Cyrus Ramavarapu
Date: 05 November 2015 
Purpose: Header file for linked_list.c
*/
#ifndef LINKED_LIST_GUARD
#define LINKED_LIST_GUARD

/* GLOBALS */
struct node{
	void        *value;
	struct node *next;
};

/* FUNCTION PROTOTYPES */

/* Returns the length of the given list */
int list_get_len(struct node *list_head);

/* Finds the first instance of a node holding in the list */
int list_locate(void *value, struct node **list_head, int (comp)(void *a, void *b));

/* Gets the node at 'position' in the given list */
struct node *list_retrieve(int position, struct node **list_head);

/* Gets position+1 entry from list */
struct node *list_next(int position, struct node **list_head);

/* Gets position-1 entry from list */
struct node *list_previous(int position, struct node **list_head);

/* Inserts 'entry' at 'position' in given list */
 /* Returns 0 on failure, 1 otherwise  */
int list_insert(struct node *entry, int position, struct node **list_head);

/* Replaces node at 'position' with 'entry' */
int list_replace(void *value, int position, struct node **list_head);

/* Removes the entry at position */
struct node *list_delete_entry(int position, struct node **list_head);

/* Returns the head of the list */
struct node *list_first(struct node **list_head);

/* Reverses the given linked list */
struct node *list_reverse(struct node **list_head);

#endif

