
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "expression.h"
#include "implication.h"
#include "conditional.h"

struct type* determine_type_of_conditional_expression(
	struct zebu_conditional_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->true_case)
	{
		type = determine_type_of_expression(expression->true_case, tcache, scope);
	}
	else if (expression->base)
	{
		type = determine_type_of_implication_expression(expression->base, tcache, scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}

