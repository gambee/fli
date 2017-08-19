#include "pdt.h"

int main(void)
{
    int i;
    struct stack stk;
    stk.top_node = NULL;
    stk.top_index = 0;
    for(i = 0; i < 15; i++)
        push(i, &stk);
    for(i=0; i<3; i++)
        pop(&stk);
    for(i=30; i<35; i++)
        push(i, &stk);
    do{
        i = pop(&stk);
        if(i>= 0)
            printf("pop: %d\n", i);
        else
            printf("Empty Stack!\n");
    }while(i >= 0);
    return 0;
}
