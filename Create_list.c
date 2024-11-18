#include "main.h"

/* 
 * Function: Create_list
 * This function converts a string representing a large number into a doubly linked list.
 * Each node in the list holds up to four digits of the number. The function also 
 * handles the sign of the number if provided.
 * 1. Check if the number has a sign; if so, set the sign and remove it from the string.
 * 2. Traverse the string from right to left, extracting up to four digits at a time.
 * 3. Convert the extracted substring to an integer and insert it at the beginning of the list.
 * 4. Repeat until the entire string is processed.
 * 5. Return SUCCESS or FAILURE based on the operation's success.
 */
Status Create_list(Op_var *op, char *oprnd) 
{
    int len, data;
    char buff[100];
    /* check the sign is + or - */
    if (!isdigit(oprnd[0]))
    {
        if (oprnd[0] == '-')
            op->sign = -1;
        else if (oprnd[0] == '+')
            op->sign = 1;

        int i = 0;

        /* Left shift the string */
        while (oprnd[i] != '\0')
        {
            oprnd[i] = oprnd[i + 1];
            i++;
        }
        op->s_flag = 1;
    }

    /* Store 4 digits in each node */
    while ((len = strlen(oprnd)) >= 4)
    {
        strcpy(buff, oprnd + len - 4);
        data = atoi(buff);

        if (insert_at_first(op, data) == FAILURE)
            return FAILURE;

        oprnd[len - 4] = '\0';
    }

    /* Copy the remaining characters to a node */
    if (len > 0)
    {
        strcpy(buff, oprnd);
        data = atoi(buff);

        if (insert_at_first(op, data) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}
