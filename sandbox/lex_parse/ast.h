#include "parser.tab.h"
#include "slee_alphabet.h"
#include "fli_buffer.h"

static char TT_condt[] = "\"->\"";
static char TT_bicnd[] = "\"<->\"";
static char TT_cjnct[] = "\"^\"";
static char TT_djnct[] = "\"v\"";
static char TT_negtn[] = "\"~\"";
static char TT_true [] = "\"T\"";
static char TT_false[] = "\"F\"";

int dot_node_index;

struct node
{
	int token_type;
	int token_value;
	struct node *left, *right;
};

char* get_token_text(int token_type)
{
	switch(token_type)
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

char get_slee_token(int token_type)
{
	switch(token_type)
	{
		case CONDT:
			return SLEE_IF;
		case BICND:
			return SLEE_IFF;
		case CJNCT:
			return SLEE_AND;
		case DJNCT:
			return SLEE_OR;
		case '~':
			return SLEE_NOT;
		case 'T': 
			return SLEE_TRUE;
		case 'F':
			return SLEE_FALSE;
		default:
			return 0;
	}
}

struct node* new_node(int token_type, struct node *left, struct node *right)
{
	dot_node_index = 0;
	struct node* tmp = (struct node*) malloc( sizeof(struct node));
	tmp->token_type = token_type;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}

int set_token_value(struct node* root, int new_value)
{
	return (int) (root ? root->token_value = new_value : 0);
}

int rec_write_postfix(struct node* root, struct BUF_buffer *buf)
{
	int count = 0;

	if(root)
	{
		if(root->left)
			count += rec_write_postfix(root->left, buf);
		if(root->right)
			count += rec_write_postfix(root->right, buf);
		
		BUF_putc(buf, get_slee_token(root->token_type));
		return count;
	}
	else return 0;
}

int write_postfix(struct node* root, char** str)
{
	int ret;
	struct BUF_buffer buffer;
	
	BUF_init(&buffer);
	ret = rec_write_postfix(root, &buffer);
	*str = *str ? (free(*str), NULL) : NULL;
	BUF_strflush(&buffer, str);
	return ret;
}


int rec_print_as_dot(struct node* root, FILE* file)
{
	int cur_dot_index = ++dot_node_index;
	int count = 0;
	if(root)
	{
		fprintf(file, "%d[label=%s];\n", cur_dot_index, get_token_text(root->token_type));
		if(root->left)
		{
			fprintf(file, "%d->%d\n", cur_dot_index, dot_node_index + 1);
			count += 1 + rec_print_as_dot(root->left, file);
		}
		if(root->right)
		{
			fprintf(file, "%d->%d\n", cur_dot_index, dot_node_index + 1);
			count += 1 + rec_print_as_dot(root->right, file);
		}
		return count;
	}
	else return 0;
}
	
int print_as_dot(FILE* file, struct node* root)
{
	int nodes = 0;
	fprintf(file, "digraph AST {\n");
	nodes = rec_print_as_dot(root, file);
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
