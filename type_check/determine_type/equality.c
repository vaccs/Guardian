
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "relational.h"
#include "equality.h"

struct type* determine_type_of_equality_expression(
	struct zebu_equality_expression* expression,
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
		type = determine_type_of_relational_expression(expression->base, tcache, scope);
	}
	
	EXIT;
	return type;
}

