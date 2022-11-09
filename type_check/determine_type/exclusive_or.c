
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "and.h"
#include "exclusive_or.h"

struct type* determine_type_of_exclusive_or_expression(
	struct zebu_exclusive_or_expression* expression,
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
		type = determine_type_of_and_expression(expression->base, tcache, scope);
	}
	
	EXIT;
	return type;
}

