
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type_cache/get_type/bool.h>

#include "equality.h"
#include "match.h"

struct type* determine_type_of_match_expression(
	struct zebu_match_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->pattern)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->base)
	{
		type = determine_type_of_equality_expression(expression->base, tcache, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

