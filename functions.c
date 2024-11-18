#include "main.h"

/* 
 * Function: validate_arg
 * This function validates the command line arguments. It checks if the number of arguments is 
 * correct and if the operator is a valid single character.
 * 1. Check if the number of arguments is less than 4. If so, print an error message and return FAILURE.
 * 2. Check if the operator string length is greater than 1. If so, print an error message and return FAILURE.
 * 3. If both checks pass, return SUCCESS.
 */
Status validate_arg(int argc, char *argv[])
{
    /* check the command line arguments is 4 */
    if (argc < 4)
    {
        printf("ERROR: Pass CLA as Operand1 Operator Operand2\n");
        return FAILURE;
    }
    if (strlen(argv[2]) > 1)
    {
        printf("ERROR: Pass the Operator as + - / x \n");
        return FAILURE;
    }
    return SUCCESS;
}

/* 
 * Function: init_op
 * This function initializes an `Op_var` structure, setting its pointers to NULL and its sign flag to default values.
 * 1. Set the `head` and `tail` pointers of the list to NULL.
 * 2. Set the `sign` to 1 (positive).
 * 3. Set the `s_flag` to 0 (no sign flag set).
 * 4. Return SUCCESS.
 */
Status init_op(Op_var *op)
{
    op->head = NULL;
    op->tail = NULL;
    op->sign = 1;
    op->s_flag = 0;
    return SUCCESS;
}

/* 
 * Function: display
 * This function displays the digits stored in the linked list, handling the sign and removing leading zeros.
 * 1. Check if the list is empty; if so, print an error message and return.
 * 2. Skip leading zeros by advancing the `head` pointer.
 * 3. Traverse the list and print each digit, adjusting the sign for the first node if necessary.
 * 4. If the list becomes empty after removing leading zeros, print 0.
 * 5. Print a newline character at the end.
 */
void display(Op_var op)
{
    /* Check if the list is empty */
    if (op.head == NULL)
    {
        printf("\nERROR: List is empty\n");
        return;
    }

    /* Remove the preceding zeros */
    while (op.head && (op.head)->data == 0)
        op.head = (op.head)->next;

    /* Display the data when the list is not empty */
    Dlist *temp = op.head;
    while (temp)
    {
        if (temp == op.head)
        {
            printf("%d", (temp->data) * (op.sign));
        }
        else
            printf("%d", temp->data);

        temp = temp->next;
    }

    /* Display zero when the list is empty */
    if (op.head == NULL)
        printf("0");
    printf("\n");
}

/* 
 * Function: node_count
 * This function counts the number of nodes in a linked list.
 * 1. Initialize a counter to 0.
 * 2. Traverse the list, incrementing the counter for each node.
 * 3. Return the total count of nodes.
 */
int node_count(Dlist *head)
{
    int count = 0;
    /* Traverse the list */
    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/* 
 * Function: compare_op
 * This function compares two linked lists representing large numbers to determine 
 * which is greater, or if they are equal.
 * 1. Count the nodes in both lists.
 * 2. If one list has more nodes, it represents the larger number.
 * 3. If both lists have the same number of nodes, compare corresponding nodes.
 * 4. Return which list is greater or if they are equal.
 */
Cmp compare_op(Dlist *op1_head, Dlist *op2_head)
{
    /* Check the node count of operator 1 and 2 */
    int op1_count = node_count(op1_head);
    int op2_count = node_count(op2_head);

    /* Depending on the node count, return */
    if (op1_count > op2_count)
    {
        return Op1_Greater;
    }
    else if (op1_count < op2_count)
    {
        return Op2_Greater;
    }
    else
    {
        /* If node counts are the same, compare the data and return the greatest value */
        Dlist *temp_op1 = op1_head;
        Dlist *temp_op2 = op2_head;

        while (temp_op1)
        {
            if (temp_op1->data < temp_op2->data)
            {
                return Op2_Greater;
            }
            else if (temp_op1->data > temp_op2->data)
            {
                return Op1_Greater;
            }

            temp_op1 = temp_op1->next;
            temp_op2 = temp_op2->next;
        }
    }

    return Equal;
}

/* 
 * Function: freeList
 * This function frees all the nodes in a linked list and resets the list pointers.
 * 1. Check if the list is empty; if so, return.
 * 2. Traverse the list and free each node.
 * 3. Set the list's `tail` pointer to NULL after freeing all nodes.
 */
void freeList(Op_var *op)
{
    /* Check if the list is empty */
    if (op->head == NULL)
    {
        return;
    }

    Dlist *temp = op->head;

    /* Traverse the list and delete one by one node */
    while (op->head != NULL)
    {
        op->head = (op->head)->next;
        free(temp);
        temp = op->head;
    }
    op->tail = NULL;

    return;
}
