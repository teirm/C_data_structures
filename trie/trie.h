/*
 * Purpose: Trie implementation
 * 
 * Author: Cyrus Ramavarapu
 * Date: 27 August 2017
 */

#ifndef TRIE_GUARD
#define TRIE_GUARD

#include <stdlib.h>

struct trie_node {
    char    domain;             /* character held by trie */
    struct  trie_node *value;    /* pointer to first cell on list for child */
    struct  trie_node *next;     /* pointer to next cell on list */
};

/*
 * Inserts a word into the trie
 */
int insert(struct trie_node **root, const char *word);

/*
 * Deletes a word, if it exists into the trie
 */
int delete_word(struct trie_node **root, const char *word);

/*
 * Creates a new node for the trie holding the given
 * character
 */
struct trie_node* create_node(const char c);


/*
 * Determines if a word exists in the trie or not
 */
int find_word(struct trie_node **root, const char *word);


#endif /* TRIE_GUARD */ 
