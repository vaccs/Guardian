
#include <debug.h>

#include <parse/parser.h>

#include "conditional.h"
#include "lambda.h"

struct expression* specialize_lambda_expression(
	struct type_cache* tcache,
	struct zebu_lambda_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_conditional_expression(tcache, zexpression->base);
	}
	else if (zexpression->lambda)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

