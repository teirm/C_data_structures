/* Author: Cyrus Ramavarapu
Date: 06 November 2015
Purpose: An array of linked lists driver
with some special functions for CS1550
project 3 */

#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.c"

#define LENGTH 4

void move_node(int from_pos, int node_pos, int to_pos, int *lengths, struct node **node_array)
{
	struct node *moved_node;
	
	moved_node = delete_entry(node_pos, &node_array[from_pos]);
	insert(moved_node, 0, &node_array[to_pos]);

	lengths[from_pos]--;
	lengths[to_pos]++;
}

void move_list(int from_pos, int to_pos, int *lengths, struct node **node_array)
{
	while (node_array[from_pos] != NULL) {	
		move_node(from_pos, 0, to_pos, lengths, node_array);
	}
}

int append_node(int new_value, struct node **list_head)
{
	int list_length;	struct node *new_node;

	list_length = get_len(*list_head);

	new_node = malloc(sizeof *new_node);
	new_node->value = new_value;


	if (insert(new_node, list_length+1, list_head))
		return 1;
	else
		return 0;
}

void traverse_list(struct node **list_head)
{
	int i;	
	int list_length;	
	struct node *current;
	
	list_length = get_len(*list_head);

	for (i = 0; i <= list_length; i++) {
		current = retrieve(i, list_head);
		printf("The value of node %d is %d.\n", i, current->value);
	}
}

void free_all(struct node **node_array)
{
	int i;
	
	for (i = 0; i < LENGTH; i++) {
		while(node_array[i] != NULL) {
			free(delete_entry(0, &node_array[i]));
		}
	}

	free(node_array);
}

int main()
{
	int i;
	int j;
	int lengths[LENGTH];
	
	struct node **node_array;

	for (i = 0; i < LENGTH; i++) {
		lengths[i] = 0;
	}

	node_array = malloc(4 * sizeof *node_array);

	for (i = 0; i < LENGTH; i++) {
		node_array[i] = malloc(sizeof *node_array[i]);
		node_array[i]->value = -1;
		lengths[i]++;
		for (j = 0; j < LENGTH; j++) {
			append_node(j, &node_array[i]);
			lengths[i]++;
		}
	}

	for (i = 0; i < LENGTH; i++) {
		printf("The values in node_array[%d] are:\n", i);
		traverse_list(&node_array[i]);
	}

	move_list(2, 1, lengths, node_array);	

	node_array[2] = malloc(sizeof *node_array[2]);
	node_array[2]->value = 99;
	lengths[2]++;

	for (i = 0; i < LENGTH; i++) {
			printf("The values in node_array[%d] are:\n", i);
			traverse_list(&node_array[i]);
	}

	move_node(2,0,1,lengths, node_array);

	free_all(node_array);

	return 0;
}
	
