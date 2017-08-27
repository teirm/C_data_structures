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
    struct trie_node *value;    /* pointer to first cell on list for child */
    struct trie_node *next;     /* pointer to next cell on list */
};

int make_null(struct trie_node *node);

int assign(struct trie_node *root, struct trie_node *node, char c);

struct trie_node* value_of(struct trie_node *root, char c);

struct trie_node* get_new(struct trie_node *root, char c);

#endif /* TRIE_GUARD */ 
