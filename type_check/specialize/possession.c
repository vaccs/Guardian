
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "possession.h"

struct expression* specialize_possession_expression(
	struct type_cache* tcache,
	struct zebu_possession_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->has)
	{
		TODO;
	}
	else
	{
		retval = specialize_lambda_expression(tcache, zexpression->base);
	}
	
	EXIT;
	return retval;
}

