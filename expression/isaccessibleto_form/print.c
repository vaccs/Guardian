
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>

#include <expression/print.h>

#include "struct.h"
#include "print.h"

struct stringtree* isaccessibleto_form_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_isaccessibleto_form);
	
	struct stringtree* tree = new_stringtree();
	
	struct isaccessibleto_form_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "isaccessibleto!(");
	
	{
		struct stringtree* sub = expression_print2(this->path);
		
		stringtree_append_tree(tree, sub);
	
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ", ");
	
	{
		struct stringtree* sub = expression_print2(this->user);
		
		stringtree_append_tree(tree, sub);
	
		free_stringtree(sub);
	}
	
	stringtree_append_printf(tree, ")");
	
	EXIT;
	return tree;
}













