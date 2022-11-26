
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/bool/struct.h>
#include <value/bool/new.h>
#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/new.h>
#include <expression/literal/struct.h>
#include <expression/logical_or/new.h>
#include <expression/inc.h>
#include <expression/free.h>

#include "logical_and.h"
#include "logical_or.h"

struct expression* specialize_logical_or_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_logical_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_logical_and_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_logical_or_expression(tcache, scope, zexpression->left);
		
		struct expression* right = specialize_logical_and_expression(tcache, scope, zexpression->right);
		
		if (left->type->kind != tk_bool || right->type->kind != tk_bool)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal)
		{
			struct literal_expression* leftlit = (void*) left;
			
			struct bool_value* leftbool = (void*) leftlit->value;
			
			if (leftbool->value)
			{
				struct value* value = new_bool_value(left->type, true);
				retval = new_literal_expression(value);
				free_value(value);
			}
			else
			{
				retval = inc_expression(right);
			}
		}
		else if (right->kind == ek_literal)
		{
			struct literal_expression* rightlit = (void*) right;
			
			struct bool_value* rightbool = (void*) rightlit->value;
			
			if (rightbool->value)
			{
				struct value* value = new_bool_value(left->type, true);
				retval = new_literal_expression(value);
				free_value(value);
			}
			else
			{
				retval = inc_expression(left);
			}
		}
		else
		{
			retval = new_logical_or_expression(left->type, left, right);
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



















