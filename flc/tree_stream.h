#include "ast.h"

#define TREE_STRM_SIZE 8

struct tree_strm_node{
	struct tree_strm_node * next;
	struct ast_node *trees[TREE_STRM_SIZE];
};

struct tree_strm{
	struct tree_strm_node *front, *back;
	int front_index, back_index;
};

void tree_strm_init(struct tree_strm *to_init)
{
	to_init->front = NULL;
	to_init->back = NULL;
	to_init->front_index = 0;
	to_init->back_index = 0;
}



int tree_strm_enq(struct tree_s
