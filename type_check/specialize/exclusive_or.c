
#include <debug.h>

#include <parse/parser.h>

#include "and.h"
#include "exclusive_or.h"

struct expression* specialize_exclusive_or_expression(
	struct type_cache* tcache,
	struct zebu_exclusive_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_and_expression(tcache, zexpression->base);
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

