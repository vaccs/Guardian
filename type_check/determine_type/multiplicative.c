
#include <assert.h>

#include <debug.h>

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
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

