/*
 * Author : Cyrus
 * Purpose: This program will differentiate polynomials
 *          using a linked list.
 * Date:  15-07-17
 */

#include <stdio.h>
#include <string.h>

#include "../doubly_linked_list.h"


#define MAX_POLY 50

#define DEBUG 0

typedef struct term {
    int     coeff;
    int     deg;
} poly_term;


void display_poly_term(
        poly_term           *term)
{
    printf("Term is: %dx^%d\n",
            term->coeff, term->deg);
}

int parse_poly(
        char                *poly)
{
    int coeff_flag              = 1;
    
    char *token                 = NULL;
    char *sub_token             = NULL;
    char *token_saver           = NULL; /* used by strtok_r to keep state */
    char *term_saver            = NULL; /* used by strtok_r to keep state */
    char *poly_counter          = NULL;
    char *term_counter          = NULL;

    const char *poly_delim      = "+";
    const char *var_delim       = "x^";
   
    poly_term test_struct       = {0, 0};

    for (poly_counter = poly; ;poly_counter = NULL) {
        token = strtok_r(poly_counter, poly_delim, &token_saver);
        if (token == NULL) {
            break;
        }
        for (term_counter = token; ;term_counter = NULL) {
            sub_token = strtok_r(term_counter, var_delim, &term_saver);
            if (sub_token == NULL) {
                break;
            }
            if (coeff_flag == 1) {
                test_struct.coeff = atoi(sub_token);
                coeff_flag = 0;
            } else {
                test_struct.deg = atoi(sub_token);
                coeff_flag = 1;
            }
        }
        display_poly_term(&test_struct);
        test_struct.coeff = 0;
        test_struct.deg = 0;
    }

    return 0;
}


/* Main entry point for the program */
int main()
{


    char test_poly[MAX_POLY] = "3x^8+4x^3+2";
    parse_poly(test_poly);

    return 0;
}

