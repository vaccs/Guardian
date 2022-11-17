
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <type/struct.h>

#include <parse/parse.h>

#include "exponentiation.h"
#include "multiplicative.h"

struct type* determine_type_of_multiplicative_expression(
	struct zebu_multiplicative_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_exponentiation_expression(expression->base, tcache, scope);
	}
	else if (expression->left)
	{
		struct type* left = determine_type_of_multiplicative_expression(expression->left, tcache, scope);
		
		struct type* right = determine_type_of_exponentiation_expression(expression->right, tcache, scope);
		
		if (left != right)
		{
			TODO;
			exit(1);
		}
		
		switch (left->kind)
		{
			case tk_int:
			case tk_float:
				type = left;
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

