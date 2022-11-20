
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include "unary.h"
#include "exponentiation.h"

struct type* determine_type_of_exponentiation_expression(
	struct zebu_exponentiation_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_unary_expression(expression->base, tcache, scope);
	}
	else if (expression->left)
	{
		struct type* subtype = determine_type_of_exponentiation_expression(expression->left, tcache, scope);
		
		switch (subtype->kind)
		{
			case tk_int:
			case tk_float:
				type = subtype;
				break;
			
			default:
				TODO;
				break;
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

