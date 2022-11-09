
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "expression.h"

struct type* determine_type_of_expression(
	struct zebu_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	struct type* type = determine_type_of_lambda_expression(expression->base, tcache, scope);
	
	EXIT;
	return type;
	#endif
}

