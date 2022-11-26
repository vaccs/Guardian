
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* list_slice_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_list_slice);
	
	struct list_slice_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->list);
	
	stringtree_append_printf(tree, "[");
	
	if (this->startindex)
	{
		struct stringtree* subtree = expression_print2(this->startindex);
		
		stringtree_append_tree(tree, subtree);
	
		free_stringtree(subtree);
	}
	
	stringtree_append_printf(tree, ":");
	
	if (this->endindex)
	{
		struct stringtree* subtree = expression_print2(this->endindex);
		
		stringtree_append_tree(tree, subtree);
	
		free_stringtree(subtree);
	}
	
	stringtree_append_printf(tree, "]");
	
	EXIT;
	return tree;
}















