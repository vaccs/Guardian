
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

/*#include <mpz/compare.h>*/

#include <parse/parse.h>

/*#include <type/struct.h>*/

/*#include <value/int/struct.h>*/

#include <value/compare.h>
#include <value/bool/new.h>
#include <value/free.h>

#include <type_cache/get_bool_type.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/comparison/new.h>
#include <expression/free.h>

#include "shift.h"
#include "relational.h"

struct expression* specialize_relational_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_relational_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_shift_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_relational_expression(tcache, scope, zexpression->left);
		
		struct expression* right = specialize_shift_expression(tcache, scope, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		struct type* type = type_cache_get_bool_type(tcache);
		
		bool all_literals = left->kind == ek_literal && right->kind == ek_literal;
		
		if (zexpression->lt)
		{
			if (all_literals)
			{
				struct literal_expression*  leftlit = (void*)  left;
				struct literal_expression* rightlit = (void*) right;
				
				int cmp = compare_values(leftlit->value, rightlit->value);
				
				struct value* value = new_bool_value(type, cmp < 0);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_comparison_expression(type, cek_less_than, left, right);
			}
		}
		else if (zexpression->gt)
		{
			if (all_literals)
			{
				struct literal_expression*  leftlit = (void*)  left;
				struct literal_expression* rightlit = (void*) right;
				
				int cmp = compare_values(leftlit->value, rightlit->value);
				
				struct value* value = new_bool_value(type, cmp > 0);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_comparison_expression(type, cek_greater_than, left, right);
			}
		}
		else if (zexpression->lte)
		{
			if (all_literals)
			{
				struct literal_expression*  leftlit = (void*)  left;
				struct literal_expression* rightlit = (void*) right;
				
				int cmp = compare_values(leftlit->value, rightlit->value);
				
				struct value* value = new_bool_value(type, cmp <= 0);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_comparison_expression(type, cek_less_than_equal_to, left, right);
			}
		}
		else if (zexpression->gte)
		{
			if (all_literals)
			{
				struct literal_expression*  leftlit = (void*)  left;
				struct literal_expression* rightlit = (void*) right;
				
				int cmp = compare_values(leftlit->value, rightlit->value);
				
				struct value* value = new_bool_value(type, cmp >= 0);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_comparison_expression(type, cek_greater_than_equal_to, left, right);
			}
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



















