#include "main.h"

/* 
 * Function: addition
 * This function adds two large numbers represented by doubly linked lists.
 * It initializes a result list, calls `add_list` to perform the addition,
 * and displays the result.
 * 1. Initialize a result list.
 * 2. Call `add_list` to perform the addition.
 * 3. If addition fails, print an error message.
 * 4. Set the result's sign and display the result.
 * 5. Return the result.
 */
Status addition(Op_var op1, Op_var op2)
{
    Op_var res;
    init_op(&res);

    /* Function call to add two lists */
    if (add_list(op1, op2, &res) == FAILURE)
    {
        printf("\nERROR: Failed to add the list\n");
    }

    /* Display the result list */
    res.sign = op1.sign;
    printf("\nAddition result is : ");
    display(res);
}

/* 
 * Function: add_list
 * This function adds two large numbers represented as doubly linked lists.
 * It traverses the lists from the least significant digit to the most significant digit,
 * adds corresponding digits with carry, and stores the result in a new list.
 * 1. Initialize carry and sum.
 * 2. Traverse both lists and add corresponding digits along with carry.
 * 3. Insert the result (modulo the base) at the beginning of the result list.
 * 4. Update carry and move to the previous nodes in the input lists.
 * 5. Return SUCCESS or FAILURE based on the operation's success.
 */
Status add_list(Op_var op1, Op_var op2, Op_var *res)
{
    int carry = 0, sum = 0, num1, num2;

    /* Traverse and add nodes */
    while (op2.tail || op1.tail || carry)
    {
        /* Add two int values of the string */
        num1 = (op1.tail) ? (op1.tail)->data : 0;
        num2 = (op2.tail) ? (op2.tail)->data : 0;

        sum = carry + num1 + num2;
        carry = sum / DIGIT;

        /* Insert the data into the result list */
        if (insert_at_first(res, sum % DIGIT) == FAILURE)
        {
            printf("ERROR: Failed to insert the node into the result list\n");
            return FAILURE;
        }

        /* Traverse to the previous node */
        op2.tail = (op2.tail) ? (op2.tail)->prev : NULL;
        op1.tail = (op1.tail) ? (op1.tail)->prev : NULL;
    }

    return SUCCESS;
}
