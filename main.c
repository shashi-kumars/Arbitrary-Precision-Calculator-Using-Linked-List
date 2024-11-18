#include "main.h"

int main(int argc,char *argv[])
{
    /* Validate the CLA */
    if(validate_arg(argc,argv) == FAILURE)
	return FAILURE;
    
    /* Declarations and initialization of variables */
    Op_var op1,op2;
    init_op(&op1);
    init_op(&op2);

    /* Create a list for the oparand variables */
    if(Create_list( &op1 , argv[1] ) == FAILURE)
    {
	printf("ERROR : Creating Oparator1 failed\n");
	return FAILURE;
    }
    if(Create_list( &op2 , argv[3] ) == FAILURE)
    {
	printf("ERROR : Creating Oparator2 failed\n");
	return FAILURE;
    }
    
    /* Switch case based of the operater */
    switch (argv[2][0])
    {
	case '+' :
	    {
		Status add;
		/* check sign of each operater based on that call functions */
		if(op1.sign * op2.sign == 1) 
		    add = addition(op1,op2);
		else 
		    add = subtraction(op1,op2); 
		/* check the funtion status */
		if(add == FAILURE)
		{
		    printf("\nERROR : Addition failed\n");
		    return FAILURE;
		}
		break;
	    }
	case '-' :
	    {
		Status sub;
		/* check operater sign and call function */
		if(op1.sign * op2.sign == -1) 
		    sub = addition(op1,op2);
		else 
		    sub = subtraction(op1,op2); 
		/* check the funtion status */
		if(sub == FAILURE)
		{
		    printf("\nERROR : Subtraction failed\n");
		    return FAILURE;
		}
		break;
	    }
	case 'x' :
	    {
		/* Call function for multilication */
		if(multiplication(op1,op2) == FAILURE)
		{
		    printf("\nERROR : Multiplication failed\n");
		    return FAILURE;
		}
		break;
	    }
	case '/' :
	    /* call function for divition */
	    if(division(op1,op2) == FAILURE)
	    {
		printf("\nERROR : Division failed\n");
		return FAILURE;
	    }
	    break;

	default :
	    /* print the promt for wrong operater */
	    printf("ERROR : Pass the Operator as + - / x\n");
    }

    return 0;
}  

