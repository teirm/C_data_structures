/* Author: Cyrus Ramavarapu
 * Date: 10 November 2015
 * Purpose: Hash table implementation using
 *          open hashing. 
 * NOTES: As of 10 Nov 2015, this is the 
 *        remenants from a CS1550 Project 3 idea
 */

/* HASH TABLE FUNCTIONS */

#include <string.h>

#include "hash_table.h"

#define DEBUG 0

#if DEBUG
#include <stdio.h>
#include <ds/debug.h>
#endif


int
hash_add(
        char                        *key,
        void                        *value,
        struct hash_table           *h_table)
{
	int hash;
	struct hash_node *new_node      = NULL;	

	hash = hash_function(key, h_table->size); 
	
	if (h_table->table[hash] == NULL) {
		h_table->table[hash] = calloc(1, sizeof *h_table->table[hash]);
	    h_table->table[hash]->key = key;	
        h_table->table[hash]->value = value;
		h_table->table[hash]->next = NULL;
        
        /* A new entry into the hash table was added 
         * starting a new chain.
         */
        h_table->entries++;
	} else {
		new_node = calloc(1, sizeof *new_node);
        new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;
		hash_append(hash, new_node, h_table->table);
	}
    return 0;
}


int 
hash_function(
       char                       *key,
       unsigned int               size)
{
    int char_sum                = 0;
    char *key_ptr               = key;
    char curr_char              = 0;

    while ((curr_char = *key_ptr++)) {
        char_sum += curr_char;
    }

	return char_sum % size;
}


void 
hash_append(
        int                         hash,
        struct hash_node            *new_node, 
        struct hash_node            **table)
{	
	struct hash_node *current_node = NULL;

	current_node = table[hash];

	while (current_node->next != NULL) {
		current_node = current_node->next;
	}
	
	current_node->next = new_node;
}


struct hash_node *
hash_delete(
        int                         hash,
        struct hash_node            **table)
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


void * 
hash_search(
        char                        *key,
        struct hash_table           *h_table)
{
	int hash;
	void *current_value            = NULL;
	struct hash_node *current_node = NULL;

	hash = hash_function(key, h_table->size);
	current_node = h_table->table[hash];

#if DEBUG
    printf("[%s:%d] The current node is %p\n",
            DEBUG_INFO, current_node);

    if (current_node) {
        printf("[%s:%d] The value at the node is %d\n",
                DEBUG_INFO, *(int *)(current_node->value));
    }

#endif


	while (current_node != NULL) {
		if (strcmp(current_node->key, key) == 0) {
		    current_value = current_node->value;
            break;
		}
        current_node = current_node->next;
	}
	
	return current_value;
}


void
free_hash(
        struct hash_table            *h_table,
        void (*free_value)(void *value))
{
	unsigned int i;
	struct hash_node *node_to_free = NULL;

	for (i = 0; i < h_table->size; i++) {
		while (h_table->table[i] != NULL) {
			node_to_free = hash_delete(i, h_table->table);

            /* The caller is responsible for freeing the 
             * contents of the node.
             */
            if (free_value) {
                free_value(node_to_free->value);
            }
			free(node_to_free);
		}
	}
}
