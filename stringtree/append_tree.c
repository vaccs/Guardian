
#include <memory/smalloc.h>

#include <debug.h>

#include "struct.h"
#include "append_tree.h"

void stringtree_append_tree(
	struct stringtree* this,
	struct stringtree* tree)
{
	ENTER;
	
	struct stringtree_node* node = smalloc(sizeof(*node));
	
	node->kind = snk_subtree;
	node->tree = tree, tree->refcount++;
	node->next = NULL;
	
	if (this->tail)
	{
		this->tail->next = node;
		this->tail = node;
	}
	else
	{
		this->head = this->tail = node;
	}
	
	EXIT;
}















