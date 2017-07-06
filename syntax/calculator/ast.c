#include "ast.h"

int main(int argc, char** argv)
{
	struct node* root = NULL;
	root = new_node(9,8,new_node(7,6,new_node(5,4,NULL,NULL),new_node(3,2,NULL,NULL)),new_node(VALUE,0,NULL,NULL));
	depth_first_display(root);
	return 0;
}

