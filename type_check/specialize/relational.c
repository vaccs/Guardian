
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <mpz/compare.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/int/struct.h>

#include <value/bool/new.h>
#include <value/free.h>

#include <type_cache/get_type/bool.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/comparison/new.h>
#include <expression/free.h>

#include "shift.h"
#include "relational.h"

struct expression* specialize_relational_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_relational_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_shift_expression(tcache, sshared, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_relational_expression(tcache, sshared, scope, zexpression->left);
		
		struct expression* right = specialize_shift_expression(tcache, sshared, scope, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression*  left_literal = (void*)  left;
			struct literal_expression* right_literal = (void*) right;
			
			struct value*  left_value =  left_literal->value;
			struct value* right_value = right_literal->value;
			
			bool result;
			
			switch (left->type->kind)
			{
				case tk_int:
				{
					struct int_value*  left_int = (void*)  left_value;
					struct int_value* right_int = (void*) right_value;
					
					int cmp = compare_mpz(left_int->integer, right_int->integer);
					
					if (zexpression->lt)
						result = cmp < 0;
					else if (zexpression->gt)
						result = cmp > 0;
					else
					{
						TODO;
					}
					break;
				}
				
				case tk_float:
					TODO;
					break;
				
				default:
					TODO;
					break;
			}
			
			struct type* bool_type = type_cache_get_bool_type(tcache);
			struct value* value_result = new_bool_value(bool_type, result);
			retval = new_literal_expression(value_result);
			free_value(value_result);
		}
		else
		{
			if (zexpression->lt)
				retval = new_comparison_expression(tcache, cek_less_than, left, right);
			else if (zexpression->gt)
				retval = new_comparison_expression(tcache, cek_greater_than, left, right);
			else if (zexpression->lte)
			{
				TODO;
			}
			else if (zexpression->gte)
			{
				TODO;
			}
			else
			{
				TODO;
			}
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



















