
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/bool/struct.h>
#include <value/bool/new.h>
#include <value/float/struct.h>
#include <value/float/new.h>
#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/new.h>
#include <expression/int_math/new.h>
#include <expression/int_math/run.h>
#include <expression/float_math/new.h>
#include <expression/literal/struct.h>
#include <expression/inc.h>
#include <expression/free.h>

#include "postfix.h"
#include "unary.h"

struct expression* specialize_unary_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_unary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_postfix_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->sub)
	{
		struct expression* subexpression = specialize_unary_expression(tcache, scope, zexpression->sub);
		
		if (zexpression->plus)
		{
			switch (subexpression->type->kind)
			{
				case tk_int:
				case tk_float:
					retval = inc_expression(subexpression);
					break;
				
				default:
					TODO;
					break;
			}
		}
		else if (zexpression->minus)
		{
			switch (subexpression->type->kind)
			{
				case tk_int:
				{
					if (subexpression->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) subexpression;
						
						struct int_value* subint = (void*) sublit->value;
						
						struct value* value = int_math_negate_run(subexpression->type, subint);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_int_math_expression(subexpression->type, imek_negate, subexpression, NULL);
					}
					break;
				}
				
				case tk_float:
				{
					if (subexpression->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) subexpression;
						
						struct float_value* subfloat = (void*) sublit->value;
						
						struct value* value = new_float_value(subexpression->type, -subfloat->value);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_float_math_expression(subexpression->type, fmek_negate, subexpression, NULL);
					}
					break;
				}
				
				default:
					TODO;
					break;
			}
		}
		else if (zexpression->lognot)
		{
			if (subexpression->type->kind != tk_bool)
			{
				TODO;
				exit(1);
			}
			
			if (subexpression->kind == ek_literal)
			{
				struct literal_expression* sublit = (void*) subexpression;
				
				struct bool_value* subbool = (void*) sublit->value;
				
				struct value* value = new_bool_value(subexpression->type, !subbool->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				TODO;
			}
		}
		else if (zexpression->bitnot)
		{
			if (subexpression->type->kind != tk_int)
			{
				TODO;
				exit(1);
			}
			
			if (subexpression->kind == ek_literal)
			{
				struct literal_expression* sublit = (void*) subexpression;
				
				struct int_value* subint = (void*) sublit->value;
				
				struct value* value = int_math_bitnegate_run(subexpression->type, subint);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_int_math_expression(subexpression->type, imek_bitnot, subexpression, NULL);
			}
		}
		else
		{
			TODO;
		}
		
		free_expression(subexpression);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













