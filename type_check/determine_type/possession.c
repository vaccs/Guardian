
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "inclusion.h"
#include "possession.h"

struct type* determine_type_of_possession_expression(
	struct zebu_possession_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	TODO;
	#if 0
	if (expression->has)
	{
		TODO;
	}
	else
	{
		type = determine_type_of_inclusion_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
	#endif
}

