/*
 *  Test program for hash table data
 *  structure.
 *
 *  Author: Cyrus Ramavarapu
 *
 *  Date: 22 July 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ds/debug.h>

#include "../hash_table.h"

#define DEBUG 1
#define MAX_KEY 15 
#define HASH_SIZE 30
#define VOID_TO_INT(x) *(int *)(x)


typedef struct test_pairs {
    char key[MAX_KEY];
    int  value;
} kv_pair;

int
test_hash_function(
        char              *key,
        unsigned int      size)
{
    int rc                      = 0;
    int char_sum                = 0;
    char *key_ptr               = key;
    char curr_char              = 0;
    while  ((curr_char = *key_ptr++)) {
        char_sum += curr_char;
    }
   
    if (char_sum % 25 == hash_function(key, size)) {
        rc = 0;
    } else {
#if DEBUG
        printf("[%s:%d] Test sum: %d\n\tHash sum: %d\n",
                DEBUG_INFO, char_sum, hash_function(key, size));
#endif
        rc = 1;
    }
    
    return rc;
}

/* Generate random data for insertion */
int
generate_test_data(
        kv_pair         **kv_list)
{
    int i;
    int j;
     


    for (i = 0; i < HASH_SIZE; ++i) {
        kv_list[i] = calloc(1, sizeof *kv_list);
        
        for (j = 0; j < MAX_KEY - 1; ++j) {
            kv_list[i]->key[j] = (rand() % 93) + 33;
        }
        kv_list[i]->key[MAX_KEY-1] = '\0';
        kv_list[i]->value = (rand() % 245); 
#if DEBUG
        printf("[%s:%d] Key: %s Value: %d\n",
                DEBUG_INFO, kv_list[i]->key, kv_list[i]->value);
#endif
    }
    return 0;
}

/* Test data insertion */
int
test_hash_add(
        kv_pair             **kv_list,
        struct hash_table   *test_table)
{
    unsigned int i;

    for (i = 0; i < test_table->size; ++i) {
        hash_add(kv_list[i]->key, &kv_list[i]->value, test_table);
    }

    if (test_table->entries == 0) {
        return 1;
    }

    return 0;
}

/* Test data retrieval */
int
test_hash_search(
        kv_pair             **kv_list,
        struct hash_table   *test_table)
{
    unsigned int i;
    void *found_value     = 0;
    
    for (i = 0; i < test_table->size; ++i) {
        found_value = hash_search(kv_list[i]->key, test_table);
       
        if (found_value == NULL) {
            return 1;
        }

        if (VOID_TO_INT(found_value) != kv_list[i]->value) {
#if DEBUG
            printf("[%s:%d] Found Value: %d\tKV Value: %d\n",
                    DEBUG_INFO, VOID_TO_INT(found_value),
                    kv_list[i]->value);
#endif
            return 1;
        }
    }
    
    return 0;
}
   
int
test_free_hash(
        struct hash_table           *test_table)
{
    free_hash(test_table, NULL); 
    return 0;
}


/* Main entry point for test suite */
int main()
{
    int i                           = 0;
    int rc                          = 0;
    char init_key[MAX_KEY]          = "cat";
    struct hash_table *test_table   = NULL;
    
    kv_pair *test_list[HASH_SIZE];


    test_table = calloc(1, sizeof *test_table);
    test_table->size = HASH_SIZE;
    test_table->table = calloc(test_table->size, sizeof *test_table->table);

    rc = test_hash_function(init_key, test_table->size);
    VERIFY_TEST(rc, "test_hash_function");
    
    rc = generate_test_data(test_list);
    VERIFY_TEST(rc, "generate_test_data"); 
    
    rc = test_hash_add(test_list, test_table);
    VERIFY_TEST(rc, "test_hash_add");
    
    rc = test_hash_search(test_list, test_table);
    VERIFY_TEST(rc, "test_hash_search");

    /* Clean up */
    rc = test_free_hash(test_table);
    VERIFY_TEST(rc, "test_free_hash");
    free(test_table->table);
    free(test_table);
    
    for (i = 0; i < HASH_SIZE; i++) {
        free(test_list[i]);
    }

    return rc;
}
