
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_dict);
	
	struct stringtree* tree = new_stringtree();
	
	struct dict_type* this = (void*) super;
	
	stringtree_append_printf(tree, "(");
	
	{
		struct stringtree* key = type_print2(this->key);
		
		stringtree_append_tree(tree, key);
		
		free_stringtree(key);
	}
	
	stringtree_append_printf(tree, " -> ");
	
	{
		struct stringtree* value = type_print2(this->value);
		
		stringtree_append_tree(tree, value);
		
		free_stringtree(value);
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}













