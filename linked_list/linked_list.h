/*Author: Cyrus Ramavarapu
Date: 05 November 2015 
Purpose: Header file for linked_list.c
*/
#ifndef LINKED_LIST_GUARD
#define LINKED_LIST_GUARD

/* GLOBALS */
struct node{
	int value;
	struct node *next;
};

/* FUNCTION PROTOTYPES */

/* Returns the length of the given list */
int get_len(struct node *list_head);

/* Finds the first instance of a node holding in the list */
int locate(int value, struct node **list_head);

/* Gets the node at 'position' in the given list */
struct node *retrieve(int position, struct node **list_head);

/* Gets position+1 entry from list */
struct node *next(int position, struct node **list_head);

/* Gets position-1 entry from list */
struct node *previous(int position, struct node **list_head);

/* Inserts 'entry' at 'position' in given list */
 /* Returns 0 on failure, 1 otherwise  */
int insert(struct node *entry, int position, struct node **list_head);

/* Replaces node at 'position' with 'entry' */
int replace(int value, int position, struct node **list_head);

/* Removes the entry at position */
struct node *delete_entry(int position, struct node **list_head);

/* Returns the head of the list */
struct node *first(struct node **list_head);

/* Reverses the given linked list */
struct node *reverse(struct node **list_head);

#endif

