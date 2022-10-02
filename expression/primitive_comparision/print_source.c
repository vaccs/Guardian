
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <type/print_source.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* primitive_comparision_expression_print_source(
	struct expression* super)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct primitive_comparision_expression* this = (void*) super;
	
	stringtree_append_printf(tree, "({");
	
	stringtree_append_tree(tree, type_print_source(this->type));
	stringtree_append_printf(tree, " left = ");
	stringtree_append_tree(tree, expression_print_source(this->left));
	stringtree_append_printf(tree, ";\n");
	
	stringtree_append_tree(tree, type_print_source(this->type));
	stringtree_append_printf(tree, " right = ");
	stringtree_append_tree(tree, expression_print_source(this->right));
	stringtree_append_printf(tree, ";\n");
	
	switch (this->type->kind)
	{
		case tk_bool:
			TODO;
			break;
		
		case tk_int:
			stringtree_append_printf(tree, "/* <int comparision> */\n");
			break;
		
		case tk_list:
			stringtree_append_printf(tree, "// <list comparision>\n");
			break;
		
		default:
		{
			dpv(this->type->kind);
			TODO;
			break;
		}
	}
	
	// free_<type>(left), free_<type>(right);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}














