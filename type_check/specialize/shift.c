
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/int_math/new.h>
#include <expression/int_math/run.h>
#include <expression/free.h>

#include "additive.h"
#include "shift.h"

struct expression* specialize_shift_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_shift_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_additive_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_shift_expression(tcache, scope, zexpression->left);
		struct expression* right = specialize_additive_expression(tcache, scope, zexpression->right);
		
		if (left->type->kind != tk_int || right->type->kind != tk_int)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression* leftlit = (void*) left;
			struct literal_expression* rightlit = (void*) right;
			
			struct int_value* leftint = (void*) leftlit->value;
			struct int_value* rightint = (void*) rightlit->value;
			
			struct value* value;
			
			if (zexpression->lshift)
				value = int_math_lshift_run(left->type, leftint, rightint);
			else if (zexpression->rshift)
				value = int_math_rshift_run(left->type, leftint, rightint);
			else
			{
				TODO;
			}
			
			retval = new_literal_expression(value);
			
			free_value(value);
		}
		else
		{
			if (zexpression->lshift)
				retval = new_int_math_expression(left->type, imek_lshift, left, right);
			else if (zexpression->rshift)
				retval = new_int_math_expression(left->type, imek_rshift, left, right);
			else
			{
				TODO;
			}
		}
		
		free_expression(left);
		free_expression(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}












