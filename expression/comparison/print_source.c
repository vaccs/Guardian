
#include <debug.h>

#include <type/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <type/print_source.h>

#include <out/shared.h>
#include <out/type_lookup/lookup.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

static const char* lookup[] = {
	[cek_equal_to] = "==",
};

struct stringtree* comparison_expression_print_source(
	struct expression* super,
	struct shared* shared)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	struct comparison_expression* this = (void*) super;
	
	switch (this->type->kind)
	{
		case tk_bool:
			TODO;
			break;
		
		case tk_char:
			TODO;
			break;
		
		case tk_float:
			TODO;
			break;
		
		case tk_int:
		case tk_list:
		{
			stringtree_append_printf(tree, "({");
			
			type_lookup(shared->tlookup, this->type);
			
			unsigned tid = this->type->id;
			
			stringtree_append_printf(tree, "type_%u *left = ", tid);
			stringtree_append_tree(tree, expression_print_source(this->left, shared));
			stringtree_append_printf(tree, ", *right = ");
			stringtree_append_tree(tree, expression_print_source(this->right, shared));
			stringtree_append_printf(tree, ";\n");
			
			TODO;
			#if 0
			stringtree_append_printf(tree, "bool cmp = compare_type_%u(left, right) %s 0;", tid, lookup[this->kind]);
			
			stringtree_append_printf(tree, "free_type_%u(left), free_type_%u(right);", tid, tid);
			
			stringtree_append_printf(tree, "cmp;", lookup[this->kind]);
			
			stringtree_append_printf(tree, "})");
			#endif
			
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return tree;
}














