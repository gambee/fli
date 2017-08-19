#include <stdio.h>
#include <string.h>

#define DEBUG
#include "fli_stack.h"

int main(void)
{
	struct STK_stack stack;

	int i;
	char c, *cur;
	char str[27];

	//build alphabet string
	for(cur = str, c = 'a'; c <= 'z'; c++, cur++)
		*cur = c;
	*cur = 0;

	STK_init(stack);

	for(i = 0, cur = str; i < 9; i++, cur++)
	{
		STK_push(&stack, *cur);
		printf("\tpushed: %c\n", *cur);
	}


	STK_printall(&stack);
	putchar('\n');

	for(i = 0; i < 3; i++)
	{
		STK_pop(&stack, &c);
		printf("\tpopped: %c\n", c);
	}

	STK_printall(&stack);

	for(i = 0; i < 5; cur++, i++)
	{
		STK_push(&stack, *cur);
		printf("\tpushed: %c\n", *cur);
	}

	STK_printall(&stack);

	
	



	





	return 0;
}
