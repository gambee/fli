struct node
{
	int tokenType;
	int value;
	struct node *left, *right;
};

struct node* new_node(int tokenType, int value, struct node *left, struct node *right)
{
	struct node* tmp = (struct node*) malloc( sizeof(struct node));
	tmp->tokenType = tokenType;
	tmp->value = value;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}
	
int depth_first_display(struct node* root)
{
	int tmp = 0;
	if(root)
	{
		tmp = depth_first_display(root->left);
		tmp += depth_first_display(root->right);
		printf("%d", root->tokenType);
		if(root->tokenType == VALUE)
			printf(": %d", root->value);
		printf(";\n");
	}
	return tmp;
}

