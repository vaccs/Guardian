
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "inclusive_or.h"
#include "logical_and.h"

struct type* determine_type_of_logical_and_expression(
	struct zebu_logical_and_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	TODO;
	#if 0
	if (expression->left)
	{
		TODO;
	}
	else
	{
		type = determine_type_of_inclusive_or_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
	#endif
}

