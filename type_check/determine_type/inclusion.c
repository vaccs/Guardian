
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "logical_or.h"
#include "inclusion.h"

struct type* determine_type_of_inclusion_expression(
	struct zebu_inclusion_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->container)
	{
		TODO;
	}
	else if (expression->base)
	{
		type = determine_type_of_logical_or_expression(expression->base, tcache, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

