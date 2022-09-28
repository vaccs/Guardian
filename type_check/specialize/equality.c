
#include <debug.h>

#include <parse/parse.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include <value/bool/new.h>
#include <value/compare.h>
#include <value/free.h>

#include <type_cache/get_type/bool.h>

#include <type/free.h>

#include "relational.h"
#include "equality.h"

struct expression* specialize_equality_expression(
	struct type_cache* tcache,
	struct zebu_equality_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_relational_expression(tcache, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_equality_expression(tcache, zexpression->left);
		
		struct expression* right = specialize_relational_expression(tcache, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression* spef_left = (void*) left, *spef_right = (void*) right;
			
			bool is_equal = !compare_value(spef_left->value, spef_right->value);
			
			dpvb(is_equal);
			
			struct type* type = type_cache_get_bool_type(tcache);
			
			struct value* value = new_bool_value(type, is_equal);
			
			retval = new_literal_expression(value);
			
			free_value(value);
			
			free_type(type);
		}
		else
		{
			TODO;
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
















