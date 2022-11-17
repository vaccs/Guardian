
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

struct stringtree* float_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_float_math);
	
	struct float_math_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
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
		{
			TODO;
/*			expression_print(this->left), printf(" + "), expression_print(this->right);*/
			break;
		}
		
		case fmek_subtract:
		{
			TODO;
/*			expression_print(this->left), printf(" - "), expression_print(this->right);*/
			break;
		}
		
		case fmek_multiply:
		{
			TODO;
/*			expression_print(this->left), printf(" * "), expression_print(this->right);*/
			break;
		}
		
		case fmek_qdivide:
		{
			struct stringtree* left = expression_print2(this->left);
			stringtree_append_tree(tree, left), free_stringtree(left);
			
			stringtree_append_printf(tree, " / ");
			
			struct stringtree* right = expression_print2(this->right);
			stringtree_append_tree(tree, right), free_stringtree(right);
			break;
		}
		
		case fmek_rdivide:
		{
			TODO;
/*			expression_print(this->left), printf(" %% "), expression_print(this->right);*/
			break;
		}
		
		case fmek_expo:
		{
			TODO;
/*			expression_print(this->left), printf(" ** "), expression_print(this->right);*/
			break;
		}
	}
	
	EXIT;
	return tree;
}

























