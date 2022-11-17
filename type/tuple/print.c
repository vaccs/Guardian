
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <list/type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* tuple_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_tuple);
	
	struct stringtree* tree = new_stringtree();
	
	struct tuple_type* this = (void*) super;
	
	stringtree_append_printf(tree, "(");
	
	unsigned i, n;
	
	for (i = 0, n = this->subtypes->n; i < n; i++)
	{
		struct stringtree* subtree = type_print2(this->subtypes->data[i]);
		
		stringtree_append_tree(tree, subtree);
		
		if (i + 1 < n)
			stringtree_append_printf(tree, ", ");
		
		free_stringtree(subtree);
	}
	
	if (n == 1)
	{
		stringtree_append_printf(tree, ", ");
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}







