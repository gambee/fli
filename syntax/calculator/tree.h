#include <stdlib.h>
#include <stdio.h>

struct node
{
	int tokenType;
	char value;
	struct node *left, *right;
};

int add_node(struct node *root)
{
	
