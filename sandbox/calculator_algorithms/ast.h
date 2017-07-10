#include <stdlib.h>
#include <stdio.h>

struct node
{
	int type;
	int value;
	struct node *left, *right;
};

struct node* new_node(int new_type, int new_value)
{
	struct node* tmp = (struct node*) malloc(sizeof(struct node));
	tmp->type = new_type;
	tmp->value = new_value;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
