/* Author: Cyrus Ramavarapu
Date: 10 November 2015
Purpose: Header file for hash table
implementation using array and linked
list.
NOTES: As of 10 Nov 2015, this is the 
remenants from a CS1550 Project 3 idea
*/

/* STRUCTS */
struct hash_node{
	long next_use;
	struct hash_node *next;
};

/* FUNCTIONS */
void init_table(struct hash_node **table);

int hash_function(unsigned int key);

void hash_add(unsigned int key, int value, struct hash_node **table);

void hash_append(int hash, struct hash_node *new_node, struct hash_node **table);

struct hash_node *hash_delete(int hash, struct hash_node **table);

int hash_find(unsigned int key, int lookup_value, struct hash_node **table);

void free_hash(struct hash_node **table);

void free_hash(struct hash_node **table);
