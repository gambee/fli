#include "parser.tab.h"

char TT_condt[] = "\"->\"";
char TT_bicnd[] = "\"<->\"";
char TT_cjnct[] = "\"^\"";
char TT_djnct[] = "\"v\"";
char TT_negtn[] = "\"~\"";
char TT_true [] = "\"T\"";
char TT_false[] = "\"F\"";

int dot_node_index;

char* get_token_text(int tokenType)
{
	switch(tokenType)
	{
		case CONDT:
			return TT_condt;
		case BICND:
			return TT_bicnd;
		case CJNCT:
			return TT_cjnct;
		case DJNCT:
			return TT_djnct;
		case '~':
			return TT_negtn;
		case 'T': 
			return TT_true;
		case 'F':
			return TT_false;
		default:
			return NULL;
	}
}

struct node
{
	int tokenType;
	struct node *left, *right;
};

struct node* new_node(int tokenType, struct node *left, struct node *right)
{
	dot_node_index = 0;
	struct node* tmp = (struct node*) malloc( sizeof(struct node));
	tmp->tokenType = tokenType;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}

int rec_print_tree(struct node* root, FILE* file)
{
	int cur_dot_index = ++dot_node_index;
	int count = 0;
	if(root)
	{
		fprintf(file, "%d[label=%s];\n", cur_dot_index, get_token_text(root->tokenType));
		if(root->left)
		{
			fprintf(file, "%d->%d\n", cur_dot_index, dot_node_index + 1);
			count += 1 + rec_print_tree(root->left, file);
		}
		if(root->right)
		{
			fprintf(file, "%d->%d\n", cur_dot_index, dot_node_index + 1);
			count += 1 + rec_print_tree(root->right, file);
		}
		return count;
	}
	else return 0;
}
	
int print_as_dot(FILE* file, struct node* root)
{
	int nodes = 0;
	fprintf(file, "digraph AST {\n");
	nodes = rec_print_tree(root, file);
	fprintf(file, "}");
	return nodes;
}
	
int save_as_dot(char* filename, struct node* root)
{
	FILE* file = NULL;
	if(file = fopen(filename, "w"))
		return print_as_dot(file, root);
	//else
	fprintf(stderr, "Failed open file: %s\n", filename);
	return -1;
}
