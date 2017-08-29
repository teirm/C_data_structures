/* 
 * Implementation of linked list trie.
 *
 * Author: Cyrus Ramavarapu
 * Date: 27 August 2017
 */

#include "trie.h"
#include <ds/debug.h>


struct trie_node*
create_node(
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
     
    int pos                         = 0;
    char current_char               = word[pos];
    struct trie_node *current_node  = root;
    struct trie_node *new_node      = NULL; 

    while (current_char != '\0') {
        
        if (current_node->domain == current_char) {
            current_char = word[pos++];
            if (current_node->value) {
                current_node = current_node->value; 
            } else {
                new_node = create_node(current_char);
                current_node->next = new_node;
            }
        } else {
            if (current_node->next) {
                current_node = current_node->next;
            } else {
                current_node->next = create_node(current_char);
            }
        }
    }

    return 0;
}

int
delete_word(
        struct trie_node            *root,
        const char                  *word)
{
}
