
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

#include "exclusive_or.h"
#include "inclusive_or.h"

struct expression* specialize_inclusive_or_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_inclusive_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_exclusive_or_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_inclusive_or_expression(tcache, scope, zexpression->left);
		struct expression* right = specialize_exclusive_or_expression(tcache, scope, zexpression->right);
		
		if (left->type->kind != tk_int || right->type->kind != tk_int)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression*  leftlit = (void*) left;
			struct literal_expression* rightlit = (void*) right;
			
			struct int_value*  leftint = (void*)  leftlit->value;
			struct int_value* rightint = (void*) rightlit->value;
			
			struct value* value = int_math_bitor_run(left->type, leftint, rightint);
			
			retval = new_literal_expression(value);
			
			free_value(value);
		}
		else
		{
			retval = new_int_math_expression(left->type, imek_bitior, left, right);
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

