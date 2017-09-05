/* 
 * Implementation of linked list trie.
 *
 * Author: Cyrus Ramavarapu
 * Date: 27 August 2017
 */

#include "trie.h"
#include <ds/debug.h>

#define DEBUG 1

#if DEBUG > 0 
#include <stdio.h>
#endif /* DEBUG */


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
        struct trie_node            **root,
        const char                  *word)
{
     
    int pos                         = 0;
    char current_char               = word[pos];
    struct trie_node *current_node  = *root;
    struct trie_node *next_node     = NULL;
    while (current_char != '\0') {

        if (!current_node) {
#if DEBUG > 0
            fprintf(stderr, "[%s:%d] creating a new root\n",
                            DEBUG_INFO);
#endif
            *root = create_node(current_char);
            current_node = *root;
        }

        if (current_node->domain == current_char) {
            current_char = word[++pos];

            if (current_char == '\0') {
                break;
            }

            if (current_node->value) {
                current_node = current_node->value;
            } else {
                current_node->value = create_node(current_char);
                current_node = current_node->value;
            }
        } else {
            if (current_node->next) {
                current_node = current_node->next;
            } else {
                current_node->next = create_node(current_char);
            }
        }
    }
    
    /* Need way of indicating end of words */
    if (current_node->value) {
       
        if (current_node->value->domain == -1) {
            /* No duplicates */ 
            return 0;
        }
       
        /* Any previous values will be contined 
         * from the current prefix.
         */
        next_node = current_node->value;
        current_node->value = create_node(-1);
        current_node->value->next = next_node;
    } else {
        current_node->value = create_node(-1);
    }

    return 0;
}


int
delete_word(
        struct trie_node            **root,
        const char                  *word)
{
    int pos                             = 0; 
    char current_char                   = word[pos]; 
    struct trie_node *current_node      = *root;

    while (current_char != '\0') {
        if (current_node->domain == current_char) {
            /* continue down prefix path */
        } else {
            if ((current_node = current_node->next) == NULL) {
                return DS_ENOTFOUND;
#if DEBUG > 0 
                printf("[%s:%d] Word %s not in trie\n",
                        DEBUG_INFO, word);
#endif /* DEBUG */
            }
        }
    } 
    return 0;
}
