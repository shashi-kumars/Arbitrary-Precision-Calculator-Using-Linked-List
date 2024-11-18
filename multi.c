#include "main.h"

/* 
 * Function: multiplication
 * This function performs multiplication of two large numbers represented by 
 * doubly linked lists. The result is stored in a separate linked list.
 * 1.Set up variables for carry,digit data, and counters.
 * 2. Traverse `op2` and for each node, multiply it by each node in `op1`, 
 *    handling carry and storing intermediate results in `r1`.
 * 3. Add the intermediate result `r1` to the cumulative result `r2`.
 * 4. Store the addition result in `r2`, reset `r1`, and shift for the next iteration.
 * 5. After processing all nodes, display the final result with the correct sign.
 * 6. Return SUCCESS or FAILURE based on the operation's success.
 */
Status multiplication(Op_var op1, Op_var op2)
{
    Op_var res, r1, r2;
    init_op(&res);
    init_op(&r1);
    init_op(&r2);

    int data = 0, carry = 0, num1, num2, count = 1;

    /* Traverse op2 to multiply with all nodes in op1 */
    while (op2.tail || carry)
    {
        num2 = (op2.tail) ? (op2.tail)->data : 0;
        Dlist *temp_tail = op1.tail;

        while (temp_tail || carry)
        {
            data = 0;
            num1 = (temp_tail) ? temp_tail->data : 0;

            data = num1 * num2 + carry;
            carry = data / DIGIT;

            /* Inserting the result into the list */
            if (insert_at_first(&r1, data % DIGIT) == FAILURE)
            {
                printf("\nERROR: Failed to insert when doing multiplication\n");
                return FAILURE;
            }

            temp_tail = (temp_tail) ? temp_tail->prev : NULL;
        }

        op2.tail = (op2.tail) ? (op2.tail)->prev : NULL;

        /* Adding the result */
        add_list(r1, r2, &res);

        /* Store the result from addition in r2 and reset r1 and res */
        if (op2.tail != NULL)
        {
            freeList(&r2);
            r2 = res;

            init_op(&res);
            init_op(&r1);

            /* Insert extra zeros at the end of r1 for the next iteration */
            int i = 0;
            while (i++ < count)
                insert_at_first(&r1, 0);
	    printf("count - %d",count);
            count++;
        }
    }

    /* Display the result with the sign */
    res.sign = op1.sign * op2.sign;
    printf("\nMultiplication is: ");
    display(res);

    return SUCCESS;
}
