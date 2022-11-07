
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/comparison/new.h>
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
	struct specialize_shared *sshared,
	struct zebu_equality_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_relational_expression(tcache, sshared, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_equality_expression(tcache, sshared, zexpression->left);
		
		struct expression* right = specialize_relational_expression(tcache, sshared, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression* spef_left = (void*) left, *spef_right = (void*) right;
			
			bool is_equal = !compare_value(spef_left->value, spef_right->value);
			
			if (zexpression->not)
				is_equal = !is_equal;
			
			dpvb(is_equal);
			
			struct value* value = new_bool_value(tcache, is_equal);
			
			retval = new_literal_expression(value);
			
			free_value(value);
		}
		else
		{
			retval = new_comparison_expression(tcache, zexpression->not ? cek_not_equal_to : cek_equal_to, left, right);
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

















