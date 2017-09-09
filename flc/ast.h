#include "parser.tab.h"
#include "slee_alphabet.h"
#include "fli_buffer.h"

static char TT_condt[] = "->";
static char TT_bicnd[] = "<->";
static char TT_cjnct[] = "^";
static char TT_djnct[] = "v";
static char TT_negtn[] = "~";
static char TT_true [] = "T";
static char TT_false[] = "F";

int dot_node_index;

struct ast_node
{
	int token_type;
	int token_value;
	struct ast_node *left, *right;
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

struct ast_node* new_node(int token_type, struct ast_node *left, struct ast_node *right)
{
	dot_node_index = 0;
	struct ast_node* tmp = (struct ast_node*) malloc( sizeof(struct ast_node));
	tmp->token_type = token_type;
	tmp->left = left;
	tmp->right = right;
	return tmp;
}

int set_token_value(struct ast_node* root, int new_value)
{
	return (int) (root ? root->token_value = new_value : 0);
}

int rec_write_postfix(struct ast_node* root, struct BUF_buffer *buf)
{
	int count = 0;

	if(root)
	{
		if(root->left)
			count += rec_write_postfix(root->left, buf);
		if(root->right)
			count += rec_write_postfix(root->right, buf);
		
		BUF_putc(buf, get_slee_token(root->token_type));
	}
	
	return count;
}

int write_postfix(struct ast_node* root, char** str)
{
	int ret;
	struct BUF_buffer buffer;
	
	BUF_init(&buffer);
	ret = rec_write_postfix(root, &buffer);
	*str = *str ? (free(*str), NULL) : NULL;
	BUF_strflush(&buffer, str);
	return ret;
}

int rec_write_infix(struct ast_node* root, struct BUF_buffer *buf)
{
	int count = 0;

	if(root)
	{
		if(root->left)
		{
			switch(root->left->token_type)
			{
				case '~':
				case 'T': 
				case 'F':
					count += rec_write_infix(root->left, buf);
					break;
				case CONDT:
				case BICND:
				case CJNCT:
				case DJNCT:
				default:
					BUF_putc(buf, '(');
					count += rec_write_infix(root->left, buf);
					BUF_putc(buf, ')');
					break;
			}
		}

		BUF_puts(buf, get_token_text(root->token_type)); 

		if(root->right)
		{
			switch(root->right->token_type)
			{
				case '~':
				case 'T': 
				case 'F':
					count += rec_write_infix(root->right, buf);
					break;
				case CONDT:
				case BICND:
				case CJNCT:
				case DJNCT:
				default:
					BUF_putc(buf, '(');
					count += rec_write_infix(root->right, buf);
					BUF_putc(buf, ')');
					break;
			}

		}
	}
	return count;
}

int write_infix(struct ast_node* root, char **str)
{
	int ret;
	struct BUF_buffer buffer;
	
	BUF_init(&buffer);
	ret = rec_write_infix(root, &buffer);
	*str = *str ? (free(*str), NULL) : NULL;
	BUF_strflush(&buffer, str);
	return ret;
}
	


int rec_print_as_dot(struct ast_node* root, FILE* file)
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
	
int print_as_dot(FILE* file, struct ast_node* root)
{
	int nodes = 0;
	fprintf(file, "digraph AST {\n");
	nodes = rec_print_as_dot(root, file);
	fprintf(file, "}");
	return nodes;
}
	
int save_as_dot(char* filename, struct ast_node* root)
{
	FILE* file = NULL;
	if((file = fopen(filename, "w")))
		return print_as_dot(file, root);
	//else
	fprintf(stderr, "Failed open file: %s\n", filename);
	return -1;
}
