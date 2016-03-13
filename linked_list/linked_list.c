/* Author: Cyrus Ramavarapu
Date: 05 November 2015 
Purpose: Linked list data structure 
*/

#include "linked_list.h"

int get_len(struct node *list_head)
{
	int length;
	struct node *current_node;	

	length = 0;
	current_node = list_head;

	while (current_node->next != NULL) {
		current_node = current_node->next;	
		length++;
	}

	return length;
}

int locate(int value, struct node **list_head)
{
	int position;
	struct node *current_node;

	position = 0;
	current_node = *list_head;

	while (value != current_node->value) {
		current_node = current_node->next;
		position++;	
	}

	return position; 
}

struct node *retrieve(int position, struct node **list_head)
{
	int node_counter;	
	struct node *current_node;

	if (position > get_len(*list_head))
		return NULL;

	current_node = *list_head;

	for (node_counter = 0; node_counter < position; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

struct node *next(int position, struct node **list_head)
{
	int node_counter;
	struct node *current_node;

	current_node = *list_head;

	if (position + 1> get_len(*list_head) || position + 1 < 0)
		return NULL;

	for (node_counter = 0; node_counter < position+1; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

struct node *previous(int position, struct node **list_head)
{
	int node_counter;
	struct node *current_node;

	current_node = *list_head;

	if (position - 1 > get_len(*list_head) || position == 0)
		return NULL;

	for (node_counter = 0; node_counter < position-1; node_counter++) {
		current_node = current_node->next;
	}

	return current_node;
}

int replace(int value, int position, struct node **list_head)
{
	struct node *selected_node;

	if (position > get_len(*list_head)+1)
		return 0;

	selected_node = retrieve(position, list_head);
	selected_node->value = value;

	return 1;
}

int insert(struct node *entry, int position, struct node **list_head)
{
	struct node *previous_node;
	struct node *next_node;	

	if (position > get_len(*list_head)+1)
		return 0;

	if (position == 0) {
		entry->next = (*list_head);	
		*list_head = entry;	
	}
	else {		
		next_node = next(position, list_head);
		previous_node = previous(position, list_head);
		entry->next = next_node;
		previous_node->next = entry;
	}	

	return 1;
}

struct node *delete_entry(int position, struct node **list_head)
{
	struct node *delete_node;
	struct node *previous_node;

	if (position > get_len(*list_head))
			return NULL;

	delete_node = retrieve(position, list_head);
	previous_node = previous(position, list_head);

	if (previous_node != NULL)	
		previous_node->next = delete_node->next;
	else
		*list_head = (*list_head)->next;

	delete_node->next = NULL;

	return delete_node;
}

struct node *first(struct node **list_head)
{
	return *list_head;
}
