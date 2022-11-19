
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

static const char* lookup[number_of_float_math_expression_kinds] = {
	[fmek_add] = "+",
	[fmek_subtract] = "-",
	[fmek_multiply] = "*",
	[fmek_qdivide] = "/",
	[fmek_rdivide] = "%",
	[fmek_expo] = "**",
};

struct stringtree* float_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct float_math_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case fmek_negate:
		{
			stringtree_append_printf(tree, "-");
			struct stringtree* subtree = expression_print2(this->left);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
			break;
		}
		
		case fmek_add:
		case fmek_subtract:
		case fmek_multiply:
		case fmek_rdivide:
		case fmek_qdivide:
		case fmek_expo:
		{
			struct stringtree* left = expression_print2(this->left);
			stringtree_append_tree(tree, left);
			
			if (!lookup[this->kind])
			{
				TODO;
			}
			
			stringtree_append_printf(tree, " %s ", lookup[this->kind]);
			
			struct stringtree* right = expression_print2(this->right);
			stringtree_append_tree(tree, right);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return tree;
}

























