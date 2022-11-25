
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/int_math/new.h>
#include <expression/int_math/run.h>
#include <expression/dict_math/new.h>
#include <expression/dict_math/run.h>
#include <expression/set_math/new.h>
#include <expression/set_math/run.h>
#include <expression/free.h>

#include <type/struct.h>

#include "match.h"
#include "and.h"

struct expression* specialize_and_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_and_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_match_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		struct expression* left = specialize_and_expression(tcache, scope, zexpression->left);
		struct expression* right = specialize_match_expression(tcache, scope, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		switch (left->type->kind)
		{
			case tk_int:
			{
				if (left->kind == ek_literal && right->kind == ek_literal)
				{
					struct literal_expression*  leftlit = (void*) left;
					struct literal_expression* rightlit = (void*) right;
					
					struct int_value*  leftint = (void*)  leftlit->value;
					struct int_value* rightint = (void*) rightlit->value;
					
					struct value* value = int_math_bitand_run(left->type, leftint, rightint);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_int_math_expression(left->type, imek_bitand, left, right);
				}
				break;
			}
			
			case tk_dict:
			{
				if (left->kind == ek_literal && right->kind == ek_literal)
				{
					struct literal_expression*  leftlit = (void*) left;
					struct literal_expression* rightlit = (void*) right;
					
					struct dict_value*  leftdict = (void*)  leftlit->value;
					struct dict_value* rightdict = (void*) rightlit->value;
					
					struct value* value = dict_math_intersect_run(left->type, leftdict, rightdict);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_dict_math_expression(left->type, dmek_intersect, left, right);
				}
				break;
			}
			
			case tk_set:
			{
				if (left->kind == ek_literal && right->kind == ek_literal)
				{
					struct literal_expression*  leftlit = (void*) left;
					struct literal_expression* rightlit = (void*) right;
					
					struct set_value*  leftset = (void*)  leftlit->value;
					struct set_value* rightset = (void*) rightlit->value;
					
					struct value* value = set_math_intersect_run(left->type, leftset, rightset);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_set_math_expression(left->type, smek_intersect, left, right);
				}
				break;
			}
			
			default:
				TODO;
				break;
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















