
#include <debug.h>

#include <parse/parser.h>

#include <type/struct.h>

#include <expression/struct.h>
#include <expression/free.h>

#include <expression/int_math/new.h>

#include "multiplicative.h"
#include "additive.h"

struct expression* specialize_additive_expression(
	struct type_cache* tcache,
	struct zebu_additive_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_multiplicative_expression(tcache, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_additive_expression(tcache, zexpression->left);
		
		struct expression* right = specialize_multiplicative_expression(tcache, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		switch (left->type->kind)
		{
			case tk_int:
				retval = new_int_math_expression(tcache, imek_add, left, right);
				break;
			
			case tk_float:
			{
				TODO;
				break;
			}
			
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



















