#include "main.h"

/*
 * Function: insert_at_last
 * Inserts a node with the given data at the end of the doubly linked list.
 * 1. Allocate memory for a new node.
 * 2. Set the data and pointers for the new node.
 * 3. If the list is empty, set the node as the head and tail.
 * 4. Otherwise, link it as the last node.
 * Input: Pointer to the list (Op_var *) and an integer (data).
 * Output: Updates the list by adding the new node at the end.
 */

void insert_at_last(Op_var *list, int data)
{
    Dlist *new_node = malloc(sizeof(Dlist));
    if (!new_node)
    {
	printf("\nERROR: Memory allocation failed\n");
	return;
    }
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL)
    {
	new_node->prev = NULL;
	list->head = new_node;
	list->tail = new_node;
    }
    else
    {
	new_node->prev = list->tail;
	list->tail->next = new_node;
	list->tail = new_node;
    }
}
/*
 * Function: remove_leading_zeros
 * Removes leading zeros from a doubly linked list representing a number.
 * 1. Traverse the list from the head.
 * 2. Remove nodes from the front if they contain the value 0.
 * 3. Stop once a non-zero node is found or the list is reduced to one node.
 */

void remove_leading_zeros(Op_var *list)
{
    while (list->head && list->head->data == 0 && list->head != list->tail)
    {
	Dlist *temp = list->head;
	list->head = list->head->next;
	list->head->prev = NULL;
	free(temp);
    }
}

/*
 * Function: estimate_quotient
 * Estimates the quotient by comparing the first few digits of the remainder and divisor.
 * 1. Compare the first digit of the remainder with the divisor.
 * 2. If the first digit is smaller, combine it with the next digit.
 * 3. Perform integer division to estimate the quotient.
 */

int estimate_quotient(Op_var remainder, Op_var divisor)
{
    int est_quotient = 0;
    Dlist *r_ptr = remainder.head;
    Dlist *d_ptr = divisor.head;

    if (r_ptr->data >= d_ptr->data)
	est_quotient = r_ptr->data / d_ptr->data;
    else
	est_quotient = (r_ptr->data * 10000 + r_ptr->next->data) / d_ptr->data;

    return est_quotient;
}

/*
 * Function: multiply_by_digit
 * Multiplies a large number (represented by a list) by a single digit.
 * 1. Traverse the list from the tail to the head.
 * 2. Multiply each node's data by the digit and handle carryover.
 * 3. Store the result in a new list.
 */
void multiply_by_digit(Op_var op, int digit, Op_var *result)
{
    int carry = 0;
    Dlist *ptr = op.tail;
    while (ptr != NULL)
    {
	int product = ptr->data * digit + carry;
	carry = product / 10000; 
	insert_at_first(result, product % 10000);
	ptr = ptr->prev;
    }
    if (carry > 0)
    {
	insert_at_first(result, carry);
    }
}
/*
 * Function: division
 * Performs division of two large numbers using a doubly linked list for each number.
 * 1. Traverse the numerator, adding digits to the remainder.
 * 2. For each digit, estimate the quotient, multiply by the divisor, and subtract from the remainder.
 * 3. Repeat until all digits are processed, forming the final quotient.
 */

Status division(Op_var op1, Op_var op2)
{
    /* Check for zero denominator */
    if ((op2.head)->data == 0)
    {
	printf("\nERROR: Denominator in the division cannot be 0\n");
	return FAILURE;
    }

    Op_var quotient, remainder;
    init_op(&quotient);
    init_op(&remainder);

    /* Initialize quotient to zero */
    insert_at_first(&quotient, 0);

    Dlist *current = op1.head;
    /* Traversing list */
    while (current != NULL)
    {
	/* Append the current digit to the remainder */
	insert_at_last(&remainder, current->data); // insert at last to avoid reversing the remainder

	/* Remove leading zeros from the remainder */
	remove_leading_zeros(&remainder);

	/* If remainder is smaller than divisor, append a zero to the quotient */
	if (compare_op(remainder.head, op2.head) == Op2_Greater)
	{
	    insert_at_last(&quotient, 0);
	}
	else
	{
	    /* Estimate the quotient digit by looking at the leading digits */
	    int estimated_quotient_digit = estimate_quotient(remainder, op2);

	    /* Subtract (estimated_quotient_digit * op2) from remainder */
	    Op_var temp, product;
	    init_op(&temp);
	    init_op(&product);
	    multiply_by_digit(op2, estimated_quotient_digit, &product);

	    if (subtract_list(remainder, product, 0, &temp) == FAILURE)
	    {
		printf("\nERROR: Failed to perform subtraction\n");
		return FAILURE;
	    }

	    /* Update remainder and store the quotient digit */
	    remainder = temp;
	    insert_at_last(&quotient, estimated_quotient_digit);
	}

	/* Move to the next digit */
	current = current->next;
    }

    /* Display the result */
    printf("\nQuotient is: ");
    display(quotient);

    /* Clean up */
    freeList(&remainder);
    freeList(&quotient);

    return SUCCESS;
}

