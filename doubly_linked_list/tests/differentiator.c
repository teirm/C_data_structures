/*
 * Author : Cyrus
 * Purpose: This program will differentiate polynomials
 *          using a linked list.
 * Date:  15-07-17
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../doubly_linked_list.h"

#define MAX_POLY 50

#define NODE_TO_POLY(x) (poly_term *)(x->value)

#define DEBUG 1

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

int differentiate_poly(
        struct dbl_node     *head)
{
    int length                          = 0;
    struct dbl_node *current_node       = NULL;
    poly_term *current_term             = NULL; 

    
    length = get_length(head);
#if DEBUG
    printf("The polynomial has %d terms\n",
            length);
#endif 
    for (current_node = head;
            current_node != NULL;
            current_node = current_node->next)
    {
#if DEBUG
        printf("[%s:%d] The current node is at %p\n",
                __FUNCTION__, __LINE__, current_node);
        printf("The current node value is at %p\n",
                current_node->value);
#endif
        if (current_node->value != NULL) {
            current_term = NODE_TO_POLY(current_node);
            display_poly_term(current_term); 
            
            if (current_term->deg != 0) {
#if DEBUG
                printf("[%s:%d] Differentiating term: ",
                        __FUNCTION__, __LINE__);
                display_poly_term(current_term);
#endif  
                current_term->coeff *= current_term->deg;
                current_term->deg -= 1;
#if DEBUG
                printf("[%s:%d] New coeff: %d\nNew deg: %d\n",
                        __FUNCTION__, __LINE__,
                        current_term->coeff, current_term->deg);
#endif
            } else {
                free(current_term);
                delete_node(current_node); 
            }
        }
    }

    return 0;
}



int parse_poly(
        char                *poly,
        struct dbl_node     *head)
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
    
    poly_term  *term_info       = NULL; /* Elements of the linked list */

    for (poly_counter = poly; ;poly_counter = NULL) {
        token = strtok_r(poly_counter, poly_delim, &token_saver);
        if (token == NULL) {
            break;
        }
        term_info = calloc(1, sizeof *term_info);
        for (term_counter = token; ;term_counter = NULL) {
            sub_token = strtok_r(term_counter, var_delim, &term_saver);
            if (sub_token == NULL) {
                break;
            }
            if (coeff_flag == 1) {
                term_info->coeff = atoi(sub_token);
                coeff_flag = 0;
            } else {
                term_info->deg = atoi(sub_token);
                coeff_flag = 1;
            }
        }
#if DEBUG
        printf("[Parse Poly]: Attempting to append the value\n");
        printf("[%s:%d]: Address of term_info: %p\n",
                __FUNCTION__, __LINE__, term_info);
#endif
        append(&head, term_info);
        display_poly_term(term_info);
    }
    return 0;
}

int clean_up(
        struct dbl_node         *head)
{
    struct dbl_node *current_node       = NULL;
    struct dbl_node *next_node          = NULL;

    for (current_node = head;
            current_node != NULL;
            current_node = next_node) {
        next_node = current_node->next;
        if (current_node->value != NULL) {
            free(current_node->value);
        }
        delete_node(current_node);
    }
    return 0;
}



/* Main entry point for the program */
int main()
{
    char test_poly[MAX_POLY]    = "3x^8+4x^3+2";
    struct dbl_node *head       = NULL;
    
    /*
     * Need to allocate the head since it 
     * is also used for storage.
     */
    head = calloc(1, sizeof *head);
    parse_poly(test_poly, head);
    differentiate_poly(head); 
    
    clean_up(head);

    return 0;
}

