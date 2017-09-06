/* 
 * Purpose: Test suite for the trie data structure
 *
 * Author: Cyrus ramavarapu
 * Date: 27 August 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <ds/debug.h>

#include "../trie.h"




int test_insert(
        struct trie_node        **root,
        char                    *word)
{
    if (insert(root, word)) {
        return 1;
    }

    return 0;
}


int test_insert_subword(
        struct trie_node        **root,
        char                    *word)
{
    if (insert(root, word)) {
        return 1;
    }

    return 0;
}

int test_insert_superword(
        struct trie_node        **root,
        char                    *word)
{
    if (insert(root, word)) {
        return 1;
    }

    return 0;
}

int test_insert_new_word(
        struct trie_node        **root,
        char                    *word)
{
    if (insert(root, word)) {
        return 1;
    }

    return 0;
}

int test_insert_new_sub_word(
        struct trie_node        **root,
        char                    *word)
{
    if (insert(root, word)) {
        return 1;
    }

    return 0;
}


/* Main entry point */
int main()
{
    int rc                       = 0;
    char *word                   = "dogs";
    char *sub_word               = "do";
    char *super_word             = "dogsby";
    char *new_word               = "fish";
    char *new_sub_word           = "fin"; 
    struct trie_node *root       = NULL;
    

    rc = test_insert(&root, word);  
    VERIFY_TEST(rc, "test_insert"); 

    rc = test_insert_subword(&root, sub_word);
    VERIFY_TEST(rc, "test_insert_subword");

    rc = test_insert_superword(&root, super_word);
    VERIFY_TEST(rc, "test_insert_superword");

    rc = test_insert_new_word(&root, new_word);
    VERIFY_TEST(rc, "test_insert_new_word");

    rc = test_insert_new_sub_word(&root, new_sub_word);
    VERIFY_TEST(rc, "test_insert_new_sub_word");

    return rc;
}
