/*
 * Author: Cyrus Ramavarapu
 * Date: 13 July 2017
 * Purpose: Doubly Linked list
 */

#include "doubly_linked_list.h"

int append(
        struct dbl_node     **head,
        void                *value)
{
    struct dbl_node *current        = NULL; 
    struct dbl_node *new_node       = NULL;
    
    new_node = calloc(1, sizeof *new_node);
    
    if (new_node == NULL) {
        return 1;
    }
    
    new_node->next = NULL;
    new_node->value = value;

    for (current = *head;
            current->next != NULL;
            current = current->next);

    current->next = new_node;
    new_node->previous = current;

    return 0;
}

int insert(
        struct dbl_node     **head,
        void                *value,
        int                 position)
{
    struct dbl_node *current        = *head;
    struct dbl_node *next_node      = NULL; 
    struct dbl_node *new_node       = NULL;

    int length = get_length(*head);

    if (position > length) {
        return 1;
    }

    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    
    next_node = current->next;
    
    new_node = calloc(1, sizeof *new_node);

    new_node->previous = current;
    new_node->next = next_node;
    new_node->value = value;

    current->next = next_node;

    if (next_node != NULL) {
        next_node->previous = new_node;
    }
    
    return 0;
}

struct dbl_node *get(
        struct dbl_node     *head, 
        int                 position)
{
    struct dbl_node *current        = head;
    int length                      = 0;

    length = get_length(head);

    if (position < 0 || position > length) {
        return NULL;
    }

    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    return current;
}

struct dbl_node *get_last(
        struct dbl_node     *head)
{
    struct dbl_node *current        = NULL;

    for (current = head;
            current->next != NULL;
            current = current->next);

    return current;
}

int get_length(
        struct dbl_node     *head)
{
    int counter                     = 0;
    struct dbl_node *current        = NULL;
    
    for (current = head;
         current != NULL;
         current = current->next) {
        counter++;
    }
    
    return counter;
}

   
