
#include <debug.h>

#include <parse/parser.h>

#include "multiplicative.h"
#include "additive.h"

struct expression* specialize_additive_expression(
	struct type_cache* tcache,
	struct zebu_additive_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_multiplicative_expression(tcache, zexpression->base);
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

