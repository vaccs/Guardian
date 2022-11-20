
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

static const char* lookup[number_of_int_math_expression_kinds] = {
	[imek_add] = "+",
	[imek_subtract] = "-",
	[imek_multiply] = "*",
	[imek_qdivide] = "/",
	[imek_rdivide] = "%",
	[imek_expo] = "**",
	
	[imek_bitand] = "&",
	[imek_bitior] = "|",
	[imek_bitxor] = "^",
	
	[imek_lshift] = "<<",
	[imek_rshift] = ">>",
};

struct stringtree* int_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct int_math_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case imek_negate:
		{
			stringtree_append_printf(tree, "-");
			struct stringtree* subtree = expression_print2(this->left);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
			break;
		}
		
		case imek_bitnot:
		{
			stringtree_append_printf(tree, "~");
			struct stringtree* subtree = expression_print2(this->left);
			stringtree_append_tree(tree, subtree);
			free_stringtree(subtree);
			break;
		}
		
		case imek_add:
		case imek_subtract:
		case imek_multiply:
		case imek_rdivide:
		case imek_qdivide:
		case imek_expo:
		case imek_bitand:
		case imek_bitxor:
		case imek_bitior:
		case imek_lshift:
		case imek_rshift:
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

























