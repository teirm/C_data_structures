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
find_word(
        struct trie_node            **root,
        const char                  *word)
{
    int pos                             = 0;
    int current_char                    = word[pos];
    struct trie_node *current_node      = NULL;

    if (!*root) {
        return DS_EEMPTY;
    }

    current_node = *root;

    while (current_char != '\0') {
        if (current_node->domain == current_char) {
            current_node = current_node->value;
            current_char = word[++pos];
        } else {
            current_node = current_node->next;
            if (current_node == NULL) {
#if DEBUG > 0 
                printf("[%s:%d] Word \"%s\" not in trie %p\n",
                        DEBUG_INFO, word, *root);
#endif /* DEBUG */
                return DS_ENOTFOUND;
            }
        }
    }
    
    if (current_node->domain != -1) {
#if DEBUG > 0 
                printf("[%s:%d] Word \"%s\" not in trie %p\n",
                        DEBUG_INFO, word, *root);
#endif /* DEBUG */
        return DS_ENOTFOUND;
    }

    return 0;
}



int
delete_word(
        struct trie_node            **root,
        const char                  *word)
{
    int i                               = 0;
    int pos                             = 0; 
    char current_char                   = word[pos];
    struct trie_node *current_node      = *root;
    struct trie_node **delete_list      = NULL;
    
    struct trie_node *delete_node       = NULL;
    struct trie_node *delete_parent     = NULL;

    if (find_word(root, word)) {
        return 1;
    }
    
    /* list of nodes to potentially delete */
    delete_list = calloc(strlen(word)+1, sizeof *delete_list);
   
    while (current_char != '\0') {
    /* 
     * current node should never be null in this loop since
     * the word is in the trie.
     */
        if (current_node->domain == current_char) {
            delete_list[pos] = current_node;
            current_node = current_node->value;
            current_char = word[++pos];
        } else {
            current_node = current_node->next;
        }
    }
    
    /* Need to get the terminating node */
    delete_list[pos] = delete_list[pos-1]->value;
  
    /* Need to delete entries from the delete list backwards.
     * If the following occurs (d is terminal):
     * 
     *   x ...  a -> b -> c ...
     *               |
     *               v
     *               d 
     * 
     * where d is deleted and then b must also be deleted, x 
     * should preceded  b if it is the previous letter.
     * Therefore traversing from x and then removing b and
     * joining a and c will the strategy.
     */

    for (i = pos; pos != 0; pos--) {
        delete_node = delete_list[pos];
        delete_parent = delete_list[pos-1];

        if (delete_node->next == NULL &&
                    delete_node->value == NULL) {
            delete_parent->value = NULL; 
            free(delete_node);
        } else if (delete_node->next != NULL) {
            if (delete_parent->value == delete_node) {
                delete_parent->value = delete_node->next;
                free(delete_node);
            } else {
                for (current_node = delete_parent->next;
                        current_node->next != delete_node;
                        current_node = current_node->next);
                current_node->next = delete_node->next;
                free(delete_node);
            }
        } else { /* delete_node->value != NULL */
            break; 
        }
    }
    
    if (!delete_list[0]->value) {
       *root = delete_list[0]->next;
       free(delete_list[0]);
    }

    /* free delete list after it is finished */
    free(delete_list);

    return 0;
}
