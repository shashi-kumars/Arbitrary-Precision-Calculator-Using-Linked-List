#include "main.h"

/* 
 * Function: insert_at_first
 * This function inserts a new node containing the given data at the beginning 
 * of a doubly linked list. It handles both empty and non-empty lists.
 * 1. Allocate memory for a new node and check for successful allocation.
 * 2. Initialize the new node with the given data and set its pointers to NULL.
 * 3. If the list is empty, set both `head` and `tail` to the new node.
 * 4. If the list is not empty, insert the new node at the beginning and update the `head`.
 * 5. Return SUCCESS or FAILURE based on the operation's success.
 */
Status insert_at_first(Op_var *op, int data)
{
    /* Create a new node and check for memory allocation */
    Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
    if (new_node == NULL)
    {
        printf("\nERROR: Memory allocation failed\n");
        return FAILURE;
    }

    /* Update the data in the new node */
    new_node->prev = NULL;
    new_node->data = data;
    new_node->next = NULL;

    /* List is empty */
    if (op->head == NULL)
    {
        op->head = new_node;
        op->tail = new_node;
        return SUCCESS;
    }

    /* Insert at first when the list is not empty */
    new_node->next = op->head;
    (op->head)->prev = new_node;
    op->head = new_node;

    return SUCCESS;
}
