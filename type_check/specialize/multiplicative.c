
#include <debug.h>

#include <parse/parser.h>

#include "exponentiation.h"
#include "multiplicative.h"

struct expression* specialize_multiplicative_expression(
	struct type_cache* tcache,
	struct zebu_multiplicative_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_exponentiation_expression(tcache, zexpression->base);
	}
	else if (zexpression->left)
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

