
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "equality.h"
#include "and.h"

struct type* determine_type_of_and_expression(
	struct zebu_and_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->left)
	{
		TODO;
	}
	else
	{
		type = determine_type_of_equality_expression(expression->base, tcache, scope);
	}
	
	EXIT;
	return type;
}

