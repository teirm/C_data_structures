/* Author: Cyrus Ramavarapu
 * Date: Tue 04 Jul 2017 08:01:41 AM EDT
 * Purpose: Header files for linked list tests
 */

int  test_length(struct node **list_head);

int  append_node(int *new_value, struct node **list_head);

void traverse_list(struct node **list_head);

void test_next(int position, struct node **list_head);

void test_previous(int position, struct node **list_head);

void test_replace(int *value, int position, struct node **list_head);

void test_insert(int *value, int position, struct node **list_head);

void test_delete(int position, struct node **list_head);

void free_all(struct node **list_head);
