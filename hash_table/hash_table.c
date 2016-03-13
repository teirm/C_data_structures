/* Author: Cyrus Ramavarapu
Date: 10 November 2015
Purpose: Hash table implementation using
array and linked list.
NOTES: As of 10 Nov 2015, this is the 
remenants from a CS1550 Project 3 idea
*/

/* HASH TABLE FUNCTIONS */
void hash_add(unsigned int key, int value, struct hash_node **table)
{
	int hash;
	struct hash_node *new_node;	

	hash = hash_function(key); 
	
	if (table[hash] == NULL) {
		table[hash] = malloc(sizeof *table[hash]);
		table[hash]->next_use = value;
		table[hash]->next = NULL;	
	} else {
		new_node = malloc(sizeof *new_node);
		new_node->next_use = value;
		new_node->next = NULL;
		hash_append(hash, new_node, table);
	}
}

void hash_append(int hash, struct hash_node *new_node, struct hash_node **table)
{	
	struct hash_node *current_node;

	current_node = table[hash];

	while (current_node->next != NULL) {
		current_node = current_node->next;
	}
	
	current_node->next = new_node;
}

struct hash_node *hash_delete(int hash, struct hash_node **table)
{
	struct hash_node *delete_node;

	if (table[hash] == NULL) {
		delete_node = NULL;	
	} else {
		delete_node = table[hash];
		table[hash] = delete_node->next;
		delete_node->next = NULL;
	}
	
	return delete_node;
}

int hash_function(unsigned int key)
{
	return key % HASH_SIZE;
}

int hash_search(unsigned int key, int lookup_value, struct hash_node **table)
{
	int hash;
	int found;
	int current_value;
	struct hash_node *current_node;

	hash = hash_function(key);
	current_node = table[hash];
	found = 0;

	while (found == 0 && current_node->next != NULL) {
		current_value = current_node->next_use;
		/* Look for first instance of a value greater than the current lookup */
		/* This will be the next used time of a page frame */
		if (current_value > lookup_value) {
			found = 1;
			lookup_value = current_value;
		}
	}
	
	return lookup_value;
}

void init_table(struct hash_node **table)
{
	int i;

	for (i = 0; i < HASH_SIZE; i++) {
		table[i] = NULL;
	}
}

void free_hash(struct hash_node **table)
{
	int i;
	struct hash_node *node_to_free;

	for (i = 0; i < HASH_SIZE; i++) {
		while (table[i] != NULL) {
			node_to_free = hash_delete(i, table);
			free(node_to_free);
		}
	}
}
