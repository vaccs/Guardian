
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "postfix.h"
#include "unary.h"

struct type* determine_type_of_unary_expression(
	struct zebu_unary_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_postfix_expression(expression->base, tcache, scope);
	}
	else
	{
		TODO; // type = determine_type_of_postfix_expression(expression->base);
	}
	
	EXIT;
	return type;
}

