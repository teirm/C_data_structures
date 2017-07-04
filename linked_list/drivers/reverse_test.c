/* A test program to test reversing a linked list */

#include <stdio.h>
#include <stdlib.h>

#include "../linked_list.h"

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

int main() {
    int i                   = 0;
    int list_length         = 0;
    
    struct node *list_head  = NULL;
    struct node *new_node   = NULL; 

    if (list_head == NULL) {
        printf("Length at start: %d\n", get_len(list_head));
    }

    list_head = malloc(sizeof *list_head);
    list_head->value = 0;

    list_head = calloc(1, sizeof *list_head);
    list_head->value = 0;
    

    for (i = 0; i < 25; ++i) {
        list_length = get_len(list_head); 
        new_node = calloc(1, sizeof *new_node);
        new_node->value = i;
        insert(new_node, list_length+1, &list_head);
    }

    traverse_list(&list_head);
    printf("Length of list: %d\n", get_len(list_head));

    list_head = reverse(&list_head);

    printf("Length of list: %d\n", get_len(list_head));
    printf("Value in the head: %d\n", list_head->value);

    traverse_list(&list_head);    

    return 0;
}
