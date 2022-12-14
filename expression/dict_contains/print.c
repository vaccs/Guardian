
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_contains_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_dict_contains);
	
	struct dict_contains_expression* this = (void*) super;
	
	struct stringtree* tree = expression_print2(this->key);
	
	stringtree_append_printf(tree, " in ");
	
	struct stringtree* sub = expression_print2(this->dict);
	stringtree_append_tree(tree, sub);
	free_stringtree(sub);
	
	EXIT;
	return tree;
}

