
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "exponentiation.h"
#include "multiplicative.h"

struct type* determine_type_of_multiplicative_expression(
	struct zebu_multiplicative_expression* expression,
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
		type = determine_type_of_exponentiation_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
	#endif
}

