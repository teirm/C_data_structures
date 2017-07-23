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

#include "../hash_table.h"

#define DEBUG 1
#define MAX_KEY 100

#define VERIFY_TEST(x, name) {\
if (x == 1) {\
    printf("[FAILURE] %s\n", name);\
} else {\
    printf("[PASSED] %s\n", name);\
}\
}

#define DEBUG_INFO __FUNCTION__, __LINE__

int
test_hash_function(
        char              *key)
{
    int rc                      = 0;
    int char_sum                = 0;
    char *key_ptr               = key;
    char curr_char              = 0;
    while  ((curr_char = *key_ptr++)) {
#if DEBUG
        printf("The current character is %c\n", curr_char);
#endif
        char_sum += curr_char;
    }
   
    if (char_sum % 25 == hash_function(key)) {
        rc = 0;
    } else {
#if DEBUG
        printf("[%s:%d] Test sum: %d\n\tHash sum: %d\n",
                DEBUG_INFO, char_sum, hash_function(key));
#endif
        rc = 1;
    }
    
    return rc;
}

/* Main entry point for test suite */
int main()
{
    int rc                      = 0;
    char init_key[MAX_KEY]      = "cat";

    rc = test_hash_function(init_key);
    VERIFY_TEST(rc, "test_hash_function");


    return rc;
}




