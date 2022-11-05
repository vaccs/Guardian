
#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>

#include <parse/parse.h>

#include "struct.h"
#include "clone.h"

struct zpexpressionset* zpexpressionset_clone(const struct zpexpressionset* this)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(this->tree->cmp, NULL);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct zebu_primary_expression* ele = node->item;
		
		inc_zebu_primary_expression(ele);
		
		avl_insert(tree, ele);
	}
	
	struct zpexpressionset* new = smalloc(sizeof(*new));
	
	new->refcount = 1;
	new->tree = tree;
	
	EXIT;
	return new;
}

