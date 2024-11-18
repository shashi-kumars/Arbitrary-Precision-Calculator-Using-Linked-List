#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DIGIT 10000

/*Enum for status */
typedef enum status
{
    FAILURE,
    SUCCESS
}Status;

/* Structure for oparands type */
typedef struct list
{
    struct node * head;
    struct node * tail;
    int sign;
    int s_flag;
}Op_var;

/* Structure to store digits of operand */
typedef struct node
{
    struct node * prev;
    unsigned int data;
    struct node * next;
} Dlist;

/* Enum for oprand compare */
typedef enum compare
{
    Op1_Greater,
    Op2_Greater,
    Equal
}Cmp;

/*function prototype*/

/* To validate command line argrumets */
Status validate_arg(int argc,char *argv[]);

/* To initilaize the oprand variables */
Status init_op(Op_var *op);

/* To create the list of oprand */
Status Create_list(Op_var *Op, char *oper);

/* To insert a four digit data node into a list */
Status insert_at_first(Op_var *, int);

/* To addtion of two list oparand */
Status addition (Op_var, Op_var);

/* To add opandeds each nodes */
Status add_list (Op_var, Op_var, Op_var *);

/* To subtract of two list */
Status subtraction(Op_var, Op_var);

/* To subtract each node of list */
Status subtract_list(Op_var, Op_var, int, Op_var *);

/* To multiply two list */
Status multiplication(Op_var, Op_var);

/* To divide two list */
Status division(Op_var, Op_var);

/* To compare two oparand for greater or equl */
Cmp compare_op(Dlist *, Dlist *);

/* To display the list */
void display (Op_var);

/* To count the number of nodes of in an list */
int node_count(Dlist *);

/* To free the list */
void freeList (Op_var *);

#endif
