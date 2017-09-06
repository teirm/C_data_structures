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

int test_find_word(
        struct trie_node        **root,
        char                    *word)
{
    if (find_word(root, word)) {
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

    rc = test_insert(&root, sub_word);
    VERIFY_TEST(rc, "test_insert_subword");

    rc = test_insert(&root, super_word);
    VERIFY_TEST(rc, "test_insert_superword");

    rc = test_insert(&root, new_word);
    VERIFY_TEST(rc, "test_insert_new_word");

    rc = test_insert(&root, new_sub_word);
    VERIFY_TEST(rc, "test_insert_new_sub_word");

    rc = test_find_word(&root, word);
    VERIFY_TEST(rc, "test_find_word_1");

    rc = test_find_word(&root, sub_word);
    VERIFY_TEST(rc, "test_find_word_2");
    
    rc = test_find_word(&root, super_word);
    VERIFY_TEST(rc, "test_find_word_3");


    return rc;
}
