
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <expression/int_math/new.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/struct.h>
#include <expression/free.h>

#include <mpz/add.h>
#include <mpz/free.h>

#include <value/int/struct.h>
#include <value/int/new.h>
#include <value/free.h>

#include "multiplicative.h"
#include "additive.h"

struct expression* specialize_additive_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_additive_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_multiplicative_expression(tcache, sshared, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_additive_expression(tcache, sshared, zexpression->left);
		
		struct expression* right = specialize_multiplicative_expression(tcache, sshared, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		if (left->kind == ek_literal && right->kind == ek_literal)
		{
			struct literal_expression* spef_left = (void*) left;
			struct literal_expression* spef_right = (void*) right;
			
			struct value* value;
			
			switch (left->type->kind)
			{
				case tk_int:
				{
					struct int_value* left_value = (void*) spef_left->value;
					struct int_value* right_value = (void*) spef_right->value;
					
					struct mpz* number;
					
					if (zexpression->add)
					{
						number = new_mpz_from_add(left_value->integer, right_value->integer);
					}
					else
					{
						TODO;
					}
					
					value = new_int_value(left->type, number);
					
					free_mpz(number);
					break;
				}
				
				case tk_float:
					TODO;
					break;
				
				default:
					TODO;
					break;
			}
			
			retval = new_literal_expression(value);
			
			free_value(value);
		}
		else switch (left->type->kind)
		{
			case tk_int:
			{
				if (zexpression->add)
				{
					retval = new_int_math_expression(tcache, imek_add, left, right);
				}
				else if (zexpression->sub)
				{
					retval = new_int_math_expression(tcache, imek_subtract, left, right);
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_float:
			{
				TODO;
				break;
			}
			
			case tk_list:
				TODO;
				break;
			
			case tk_lambda:
				TODO;
				break;
			
			default:
				TODO;
				break;
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



















