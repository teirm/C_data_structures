/* 
 * Implementation of linked list trie.
 *
 * Author: Cyrus Ramavarapu
 * Date: 27 August 2017
 */

#include "trie.h"

struct trie_node*
create_node(
        struct trie_node            *root,
        const char                      c)
{
    struct trie_node *new_node      = NULL;

    new_node = calloc(1, sizeof *new_node);

    new_node->domain = c;
    new_node->value = NULL;
    new_node->next = NULL;

    return new_node;
}

int
insert(
        struct trie_node            *root,
        const char                  *word)
{
}

int
delete_word(
        struct trie_node            *root,
        const char                  *word)
{
}
