
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
		
		case imek_add:
		{
			TODO;
/*			expression_print(this->left), printf(" + "), expression_print(this->right);*/
			break;
		}
		
		case imek_subtract:
		{
			struct stringtree* left = expression_print2(this->left);
			stringtree_append_tree(tree, left);
			
			stringtree_append_printf(tree, " - ");
			
			struct stringtree* right = expression_print2(this->right);
			stringtree_append_tree(tree, right);
			
			free_stringtree(left), free_stringtree(right);
			break;
		}
		
		case imek_multiply:
		{
			TODO;
/*			expression_print(this->left), printf(" * "), expression_print(this->right);*/
			break;
		}
		
		case imek_qdivide:
		{
			TODO;
/*			expression_print(this->left), printf(" / "), expression_print(this->right);*/
			break;
		}
			
		case imek_rdivide:
		{
			TODO;
/*			expression_print(this->left), printf(" %% "), expression_print(this->right);*/
			break;
		}
		
		case imek_expo:
		{
			TODO;
/*			expression_print(this->left), printf(" ** "), expression_print(this->right);*/
			break;
		}
		
		case imek_bitnot:
		{
			TODO;
/*			printf("~"), expression_print(this->left);*/
			break;
		}
		
		case imek_bitand:
		{
			TODO;
/*			expression_print(this->left), printf(" & "), expression_print(this->right);*/
			break;
		}
		
		case imek_bitxor:
		{
			TODO;
/*			expression_print(this->left), printf(" ^ "), expression_print(this->right);*/
			break;
		}
		
		case imek_bitior:
		{
			TODO;
/*			expression_print(this->left), printf(" | "), expression_print(this->right);*/
			break;
		}
		
		case imek_lshift:
		{
			TODO;
/*			expression_print(this->left), printf(" << "), expression_print(this->right);*/
			break;
		}
		
		case imek_rshift:
		{
			TODO;
/*			expression_print(this->left), printf(" >> "), expression_print(this->right);*/
			break;
		}
	}
	
	EXIT;
	return tree;
}

























