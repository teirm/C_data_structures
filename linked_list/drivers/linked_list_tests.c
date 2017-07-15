/* Author: Cyrus Ramavarapu
Date: 01 November 2015 
Purpose: Test program to ensure functionality of 
linked list data structure
*/

#include <stdlib.h>
#include <stdio.h>

#include "../linked_list.h"
#include "linked_list_tests.h"


int main() {
	int i                           = 0;
	struct node *list_head          = NULL;

	printf("A test program for the linked list data structure\n");

	if (list_head == NULL) {
		printf("Length at start: %d\n", get_len(list_head)); 
    }

	list_head = calloc(1, sizeof *list_head);
	list_head->value = 0;
/**********************************************************************/
	printf("Test 1: Get length of the list\n");

/*	printf("The length of the list is: %d\n", test_length(list_head)); */
/**********************************************************************/
	printf("Test 2: Add nodes to end of linked list\n");

	for (i = 1; i < 25; i++) {
		append_node(i, &list_head);
	}
    printf("Length of list is: %d\n", get_len(list_head));
/**********************************************************************/
	printf("Test 3: Traverse list\n");
	
	traverse_list(&list_head); 
/**********************************************************************/
	printf("Test 4: Test positional functions NEXT and PREVIOUS\n");

	for (i = 0; i < 24; i++) {
		test_next(i, &list_head);
	}

	for (i = get_len(list_head); i > 0; i--) {
		test_previous(i, &list_head);
	} 
/**********************************************************************/
	printf("Test 5: Replacement test\n");

	test_replace(999, 13, &list_head); 
/**********************************************************************/
	printf("Test 6: Insertion test\n");

	test_insert(888, 8, &list_head); 
/**********************************************************************/
	printf("Test 7: Deletion test\n");

	test_delete(0, &list_head); 
    
/**********************************************************************/
   
    printf("Test 7: Reversal test\n");
    list_head = reverse(&list_head);

/**********************************************************************/
	printf("Test 8: Free all\n");

	free_all(&list_head);
    
/**********************************************************************/
	return 0;
}

int test_length(struct node **list_head)
{
	return  get_len(*list_head);
}

int append_node(int new_value, struct node **list_head)
{
	int list_length;
    struct node *new_node;

	list_length = get_len(*list_head);

	new_node = calloc(1, sizeof *new_node);
	new_node->value = new_value;

	if (insert(new_node, list_length+1, list_head)) {
		return 1;
    } else {
        printf("Returning zero\n");
		return 0;
    }
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

void test_next(int position, struct node **list_head)
{
	struct node *current;

	current = next(position, list_head);
	printf("The node after position %d has the value %d\n", position, current->value);
}

void test_previous(int position, struct node **list_head)
{
	struct node *current;

	current = previous(position, list_head);
	printf("The node before position %d has the value %d\n", position, current->value);
}

void test_replace(int new_value, int position, struct node **list_head)
{
	replace(new_value, position, list_head);

	traverse_list(list_head);
}

void test_insert(int new_value, int position, struct node **list_head)
{
	struct node *new_node;
    

	new_node = calloc(1, sizeof *new_node);
	new_node->value = new_value;

	insert(new_node, position, list_head);

	traverse_list(list_head);
}

void test_delete(int position, struct node **list_head)
{
	struct node *removed_node;

	removed_node = delete_entry(position, list_head);

	printf("The value of removed node at position %d is %d\n", position, removed_node->value);
    free(removed_node);

	printf("The list is now:\n");

	traverse_list(list_head);
}

void free_all(struct node **list_head)
{
	int i;

	for (i = get_len(*list_head); i > 0; --i) {
		free(delete_entry(i, list_head));
	}
    free(*list_head);
}
