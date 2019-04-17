/*
Weiting Tan
JHED: wtan12
*/

#ifndef _LABEL_H
#define _LABEL_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LABEL_SIZE 32


/* A label type node in the linked list data structure*/
typedef struct dummy_node {
        char str[LABEL_SIZE]; // Store string name of label.
        int add; // Store address of label.
        struct dummy_node *next;
} Label;

/*
 * Initialize the linked list.
 */
void init_list();

/*
 * Free the entire linked list.
 */ 
void freeList();

/*
 * Update the address of the label with the input name.
 */
void updateLabel(const char *name, int add);

/*
 * Get the address of a specific label
 */
int getLabelAdd(const char *name);

/*
 * Append a new label to the tail of the linked list with specified name and address.
 */
void append(const char *name, int add);

/*
 * Check of the label of the name exist or not. Return 1 on exist and 0 otherwise.
 */
int find(const char *name);

/*
 * Iterate the entire list and check if any label is used but not defined.
 */
void checkList();

#endif
