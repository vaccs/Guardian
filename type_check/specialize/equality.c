
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/comparison/new.h>
#include <expression/free.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/stream.h>
#include <stringtree/free.h>

#include <value/bool/new.h>
#include <value/compare.h>
#include <value/free.h>

#include <type_cache/get_bool_type.h>

#include <type/print.h>

#include "relational.h"
#include "equality.h"

struct expression* specialize_equality_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_equality_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_relational_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_equality_expression(tcache, scope, zexpression->left);
		
		struct expression* right = specialize_relational_expression(tcache, scope, zexpression->right);
		
		if (left->type != right->type)
		{
			fflush(stdout);
			
			struct stringtree* tree = new_stringtree();
			
			stringtree_append_printf(tree, "%s: incompatible types for comparision '", argv0);
			
			struct stringtree* lefttree = type_print2(left->type);
			
			stringtree_append_tree(tree, lefttree);
			stringtree_append_printf(tree, "' and '");
			
			struct stringtree* righttree = type_print2(right->type);
			
			stringtree_append_tree(tree, righttree);
			stringtree_append_printf(tree, "'!\n");
			
			stringtree_stream(tree, stderr);
			
			exit(e_bad_input_file);
			
			free_stringtree(lefttree);
			free_stringtree(righttree);
			free_stringtree(tree);
		}
		
		struct type* type = type_cache_get_bool_type(tcache);
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression* spef_left = (void*) left, *spef_right = (void*) right;
			
			int cmp = compare_values(spef_left->value, spef_right->value);
			
			bool is_equal = zexpression->e ? cmp == 0 : cmp != 0;
			
			dpvb(is_equal);
			
			struct value* value = new_bool_value(type, is_equal);
			
			retval = new_literal_expression(value);
			
			free_value(value);
		}
		else
		{
			retval = new_comparison_expression(type, zexpression->n
				? cek_not_equal_to : cek_equal_to, left, right);
		}
		
		free_expression(left), free_expression(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















