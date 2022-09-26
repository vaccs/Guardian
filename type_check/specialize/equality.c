
#include <debug.h>

#include <parse/parser.h>

#include "relational.h"
#include "equality.h"

struct expression* specialize_equality_expression(
	struct type_cache* tcache,
	struct zebu_equality_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_relational_expression(tcache, zexpression->base);
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
