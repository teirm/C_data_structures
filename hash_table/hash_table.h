/* Author: Cyrus Ramavarapu
Date: 10 November 2015
Purpose: Header file for hash table
implementation using array and linked
list.
NOTES: As of 10 Nov 2015, this is the 
remenants from a CS1550 Project 3 idea
*/

#ifndef OPEN_HASH_GUARD
#define OPEN_HASH_GUARD

#include <stdlib.h>

struct hash_table{
    unsigned int size;
    unsigned int entries;
    struct hash_node **table;
};

/* STRUCTS */
struct hash_node{
    char *key;
	void *value;
	struct hash_node *next;
};

/* FUNCTIONS */
int hash_add(char *key, void *value, struct hash_table *table);

int hash_function(char *key, unsigned int size);

void hash_append(int hash, struct hash_node *new_node, struct hash_node **table);

struct hash_node *hash_delete(int hash, struct hash_node **table);

void *hash_search(char *key, struct hash_table *table); 

void free_hash(struct hash_table *h_table, void (*free_value)(void *value));
struct hash_node *hash_delete(int hash, struct hash_node **table);

unsigned int get_table_length(struct hash_table *table);
#endif
