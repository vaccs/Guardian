
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/bool/struct.h>
#include <value/bool/new.h>
#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/implication/new.h>
#include <expression/bool_not/new.h>
#include <expression/inc.h>
#include <expression/free.h>

#include "possession.h"
#include "implication.h"

struct expression* specialize_implication_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_implication_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->implies)
	{
		struct expression* left =
			specialize_possession_expression(tcache, scope, zexpression->base);
		
		struct expression* right =
			specialize_implication_expression(tcache, scope, zexpression->implies);
		
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
				retval = inc_expression(right);
			}
			else
			{
				struct value* value = new_bool_value(left->type, true);
				retval = new_literal_expression(value);
				free_value(value);
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
				retval = new_bool_not_expression(left->type, left);
			}
		}
		else
		{
			retval = new_implication_expression(left->type, left, right);
		}
		
		free_expression(left);
		free_expression(right);
	}
	else
	{
		retval = specialize_possession_expression(tcache, scope, zexpression->base);
	}
	
	EXIT;
	return retval;
}






















