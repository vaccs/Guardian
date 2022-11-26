
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type_cache/get_int_type.h>

#include "additive.h"
#include "shift.h"

struct type* determine_type_of_shift_expression(
	struct zebu_shift_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->left)
	{
		type = type_cache_get_int_type(tcache);
	}
	else if (expression->base)
	{
		type = determine_type_of_additive_expression(expression->base,
			tcache, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

