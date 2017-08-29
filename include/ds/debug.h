/*
 * Purpose: Debugging macros and functions.
 *
 * Author: Cyrus Ramavarapu
 * Date 23 July 2017
 */

/* Test verification */
#define VERIFY_TEST(x, name) {\
if (x == 1) {\
    printf("[FAILURE] %s\n", name);\
} else {\
    printf("[PASSED] %s\n", name);\
}\
}

/* Debugging printf info */
#define DEBUG_INFO __FUNCTION__, __LINE__

/* Error codes */
#define DS_ENOTFOUND 0x001
#define DS_ENOMEM    0x002
#define DS_EIO       0x003
