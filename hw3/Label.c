/*
Weiting Tan
JHED:wtan12
 */

#include "Label.h"


Label *head;
Label *tail;

void init_list()
{
    head = NULL;
    head = malloc(sizeof(Label));
    if (head == NULL)
    {
        fprintf(stderr, "Error: assembler linked list initialization failed.\n");
        exit(9);
    }
    tail = head; // last and only element is head
    head->next = NULL;
    strcpy(head->str, "");
}

/*
 * Free the entire linked list.
 */
void freeList()
{
    Label *current = head;
    Label *nextLabel = NULL;
    while (current != NULL)
    {
        nextLabel = current->next;
        current->add =0;
        free(current);
        current = NULL;
        current = nextLabel;
    }
    head = NULL;
}

/*
 * Update the address of the label with the input name.
 */
void updateLabel(const char *name, int add)
{
    Label *current = head;
    while (current != NULL)
    {
        if (strcmp(current->str, name) == 0)
        {
            current->add = add;
            return;
        }
        current = current->next;
    }
    fprintf(stderr, "Error: assembler label address update failed.Label \"%s\"doesn't "
                    "exist.\n",
            name);
    exit(EXIT_FAILURE);
}

/*
 * Get the address of a specific label
 */
int getLabelAdd(const char *name)
{
    Label *current = head;
    while (current != NULL)
    {
        if (strcmp(current->str, name) == 0)
        {
            return current->add;
        }
        current = current->next;
    }
    fprintf(stderr, "Error: assembler label get address failed. Label \"%s\"doesn't "
                    "exist.\n",
            name);
    exit(EXIT_FAILURE);
}

/*
 * Append a new label to the tail of the linked list with specified name and address.
 */
void append(const char *name, int add)
{
    tail->next = malloc(sizeof(Label));
    if (tail->next == NULL)
    {
        printf("malloc error when appending lablels.\n");
        exit(9);
    }
    strncpy(tail->next->str, name, strlen(name));
    tail->next->add = add;
    tail = tail->next; // new tail
}

/*
 * Check of the label of the name exist or not. Return 1 on exist and 0 otherwise.
 */
int find(const char *name)
{
    Label *current = head;
    while (current != NULL)
    {
        if (strcmp(current->str, name) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/*
 * Iterate the entire list and check if any label is used but not defined.
 */
void checkList()
{
    Label *current = head;
    while (current != NULL)
    {
        if (current->add == -1)
        {
            fprintf(stderr, "Error: label \"%s\" is used but not defined.\n",
                    current->str);
            exit(7);
        }
        current = current->next;
    }
}

/* toString method to help checking the label and its value.*/
void toString()
{
    Label *current = head;
    if (head == NULL)
    {
        return;
    }
    while (current != NULL)
    {
        printf("label %s has value %d\n", current->str, current->add);
        current = current->next;
    }
}
