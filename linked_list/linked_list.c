/* Author: Cyrus Ramavarapu
Date: 05 November 2015 
Purpose: Linked list data structure 
*/

#include <stdlib.h>
#include <stdio.h>

#include <ds/debug.h>

#include "linked_list.h"

#define LINKED_LIST_DEBUG 1

int 
list_get_len(
    struct node *list_head)
{
	int length;
	struct node *current_node;	

	length = 0;
	current_node = list_head;

    /* Need to check if the list even exists */
    while (current_node != NULL && current_node->next != NULL) {
        current_node = current_node->next;	
        length++;
    }

	return length;
}

int
list_locate(
    void *value,
    struct node **list_head,
    int (comp)(void *a, void *b))
{
	int position;
	struct node *current_node;

	position = 0;
	current_node = *list_head;

	while (comp(value, current_node->value) != 0) {
		current_node = current_node->next;
		position++;	
	}

	return position; 
}

struct node *
list_retrieve(
    int         position,
    struct node **list_head)
{
	int node_counter;	
	struct node *current_node;

	if (position > list_get_len(*list_head)) {
		return NULL;
    }

	current_node = *list_head;

	for (node_counter = 0; node_counter < position; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

struct node *
list_next(
    int         position,
    struct node **list_head)
{
	int node_counter;
	struct node *current_node;

	current_node = *list_head;

	if (position + 1> list_get_len(*list_head) || position + 1 < 0) {
		return NULL;
    }

	for (node_counter = 0; node_counter < position+1; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

struct node *
list_previous(
    int         position,
    struct node **list_head)
{
	int node_counter;
	struct node *current_node;

	current_node = *list_head;

	if (position - 1 > list_get_len(*list_head) || position == 0) {
		return NULL;
    }

	for (node_counter = 0; node_counter < position-1; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

int 
list_replace(
    void *value,
    int position,
    struct node **list_head)
{
	struct node *selected_node;

	if (position > list_get_len(*list_head)+1) {
		return 0;
    }

	selected_node = list_retrieve(position, list_head);
	selected_node->value = value;

	return 1;
}

int 
list_insert(
    struct node     *entry,
    int             position,
    struct node     **list_head)
{
	struct node *previous_node;
	struct node *next_node;	

	if (position > list_get_len(*list_head)+1) {
		return 1;
    }

	if (position == 0) {
		entry->next = (*list_head);	
		*list_head = entry;	
	} else {
        /* The next node is the node at this position.
         * we don't want to accidently drop a node by
         * skipping it.
         */
		next_node = list_retrieve(position, list_head);
		previous_node = list_previous(position, list_head);
		entry->next = next_node;
		previous_node->next = entry;
	}	

	return 0;
}

int
list_append(
    struct node         *entry,
    struct node         **list_head)
{

    int list_length = list_get_len(*list_head);
#ifdef LINKED_LIST_DEBUG
    printf("[%s:%d] list_length=%d\n",
            DEBUG_INFO, list_length);
#endif /* LINKED_LIST_DEBUG */

    
    return list_insert(entry, list_length, list_head);
}

struct node *
list_delete_entry(
    int position,
    struct node **list_head)
{
	struct node *delete_node;
	struct node *previous_node;

    if (*list_head == NULL) {
        return NULL;
    }
	
    if (position > list_get_len(*list_head)) {
        return NULL;
    }

	delete_node = list_retrieve(position, list_head);
	previous_node = list_previous(position, list_head);

	if (previous_node != NULL) {	
		previous_node->next = delete_node->next;
    } else {
        *list_head = (*list_head)->next;
    }

	delete_node->next = NULL;

	return delete_node;
}

struct node *
list_first(
    struct node **list_head)
{
	return *list_head;
}

struct node *
list_reverse(
    struct node **list_head)
{
    struct node *current_node      = NULL;
    struct node *next_node       = NULL;    
    struct node *reverse         = NULL; 

    current_node = *list_head;
    next_node = current_node->next;

    while (next_node != NULL) {
        current_node->next = reverse;
        reverse = current_node;
        current_node = next_node;
        next_node = current_node->next;
    }

    current_node->next = reverse;
    reverse = current_node;
    
    return reverse;
}
