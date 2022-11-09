
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "implication.h"
#include "conditional.h"

struct type* determine_type_of_conditional_expression(
	struct zebu_conditional_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	TODO;
	#if 0
	if (expression->true_case)
	{
		TODO;
	}
	else
	{
		type = determine_type_of_implication_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
	#endif
}

