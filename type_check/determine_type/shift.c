
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

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
		TODO;
	}
	else
	{
		type = determine_type_of_additive_expression(expression->base,
			tcache, scope);
	}
	
	EXIT;
	return type;
}

