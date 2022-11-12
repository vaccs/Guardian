
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type_cache/get_type/int.h>

#include "exclusive_or.h"
#include "inclusive_or.h"

struct type* determine_type_of_inclusive_or_expression(
	struct zebu_inclusive_or_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_exclusive_or_expression(expression->base, tcache, scope);
	}
	else if (expression->left)
	{
		type = type_cache_get_int_type(tcache);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

