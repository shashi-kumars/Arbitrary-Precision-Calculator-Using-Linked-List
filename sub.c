#include "main.h"

/* 
 * Function: subtraction
 * This function performs the subtraction of two large numbers represented by
 * doubly linked lists. It determines which operand is larger and calls the
 * subtraction helper function accordingly.
 * 1. Initialize the result list `res`.
 * 2. Compare the two operands `op1` and `op2` to determine which is larger.
 * 3. If `op1` is greater or equal to `op2`, subtract `op2` from `op1`.
 * 4. If `op2` is greater than `op1`, subtract `op1` from `op2` and adjust the sign.
 * 5. Display the final result with the correct sign.
 * 6. Return SUCCESS or FAILURE based on the operation's success.
 */
Status subtraction(Op_var op1, Op_var op2)
{
    Op_var res;
    init_op(&res);

    Cmp large = compare_op(op1.head, op2.head);

    /* When op1 is greater or equal to op2, flag sent as 0 */
    if (large == Op1_Greater || large == Equal)
    {
        if (subtract_list(op1, op2, 0, &res) == FAILURE)
        {
            printf("\nERROR: Failed to perform subtraction\n");
            return FAILURE;
        }
        if (op1.s_flag)
            res.sign = op1.sign;
    }
    else if (large == Op2_Greater) // When op2 > op1
    {
        if (subtract_list(op2, op1, 1, &res) == FAILURE)
        {
            printf("\nERROR: Failed to perform subtraction\n");
            return FAILURE;
        }

        if (op2.s_flag)
            res.sign = op2.sign;
    }

    /* Display the result */
    printf("\nSubtraction is: ");
    display(res);

    return SUCCESS;
}

/* 
 * Function: subtract_list
 * This helper function performs the digit-by-digit subtraction of two lists.
 * It handles borrowing and stores the result in a separate list.
 * 1. Initialize variables for borrowing, data, and digits of `op1` and `op2`.
 * 2. Traverse the lists from tail to head, subtracting digits and managing borrow.
 * 3. Insert the resulting digit into the result list `res`.
 * 4. After processing, remove leading zeros from the result list.
 * 5. If a flag is set, mark the result as negative.
 * 6. Return SUCCESS or FAILURE based on the operation's success.
 */
Status subtract_list(Op_var op1, Op_var op2, int flag, Op_var *res)
{
    int borrow = 0, data = 0, num1, num2;

    while (op1.tail || op2.tail)
    {
        num1 = (op1.tail) ? (op1.tail)->data : 0;
        num2 = (op2.tail) ? (op2.tail)->data : 0;

        /* Check if there is borrow */
        if (borrow)
        {
            num1 -= borrow;
            (op1.tail)->data = num1;
            borrow = 0;
        }

        /* Calculate the result and store it in the result list */
	if(num1 >= num2)
	{
	    data = num1 - num2;
	}
	else if (num1 < num2)
	{
	    data = (num1 + DIGIT) - num2;
	    borrow = 1;
	}

	/*store the result data*/
	if(insert_at_first(res, data )==FAILURE)
	{
	    printf("\nERROR : when perfoming insert in subtraction\n");
	    return FAILURE;
	}

	op1.tail = (op1.tail) ? (op1.tail)->prev : NULL;
	op2.tail = (op2.tail) ? (op2.tail)->prev : NULL;
    }

    /*remove leading zeros*/
    while( (res->head != res->tail) && ((res->head)->data==0))
    {
	res->head= (res->head)->next;
    }

    /*if flag present to add - sign at the begining*/
    if(flag)
    {
	res->sign = -1;
    }

    return SUCCESS;

}


