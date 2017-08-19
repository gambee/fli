/* pdt.h 
 * This is an implementation of a Pushdown Transducer Automoton
 * that will serve to calculate the values of logical expressions.
 */

//tempory enum for tokens
enum {CONDT, BICND, CJNCT, DJNCT}

#include <stdio.h>
#include <stdlib.h>

//the stack
#define NODE_SIZE 5
struct stack_node
{
    int data[NODE_SIZE];
    struct stack_node* next;
};

//an instance of the stack
struct stack
{
    struct stack_node* top_node;
    int top_index;
};


int push(int input, struct stack* stk)
{
    if(!stk)
        return -1;
    if(stk->top_node)
    {
        if(stk->top_index < NODE_SIZE)
            stk->top_node->data[stk->top_index++] = input;
        else
        {
            struct stack_node* tmp = stk->top_node;
            stk->top_node = (struct stack_node*) malloc(sizeof(struct stack_node));
            stk->top_node->next = tmp;
            stk->top_node->data[0] = input;
            stk->top_index = 1;
        }
    }
    else
    {
        stk->top_node = (struct stack_node*) malloc(sizeof(struct stack_node));
        stk->top_node->next = NULL;
        stk->top_node->data[0] = input;
        stk->top_index = 1;
    }
    return 0;
}

int pop(struct stack* stk)
{
    int ret;
    struct stack_node* tmp = NULL;
    if(!stk)
        return -1;
    if(!stk->top_node)
        return -2;

    ret = stk->top_node->data[--stk->top_index];
    if(stk->top_index == 0)
    {
        tmp = stk->top_node;
        stk->top_node = stk->top_node->next;
        free(tmp);
        stk->top_index = NODE_SIZE-1;
    } return ret;
}

int display(struct stack* stk)
{
    if(!stk)
        return -1;
    int count = 0;
    int i = stk->top_index;
    struct stack_node* cur = stk->top_node;
    while(cur)
    {
        printf("Node %d:\n", count++);
        do{
            printf("\tdata[%d]: %d\n", i, cur->data[--i]);
        }while(i);
        cur = cur->next;
        i = NODE_SIZE -1;
    }
    return count;
}

/* The PDT Instance */
struct PDT
{
    int state;
    struct stack stk;
}

int transition(int state, int input, struct stack* stk)
{
    switch(state)
    {
        case 0:
            switch(input)
            {
                case 



