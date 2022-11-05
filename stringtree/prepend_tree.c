
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "prepend_tree.h"

void stringtree_prepend_tree(
	struct stringtree* this,
	struct stringtree* tree)
{
	ENTER;
	
	struct stringtree_node* node = smalloc(sizeof(*node));
	
	node->is_branch = true;
	node->tree = tree, tree->refcount++;
	node->next = NULL;
	
	if (this->head)
	{
		node->next = this->head;
		this->head = node;
	}
	else
	{
		this->head = this->tail = node;
	}
	
	EXIT;
}















