
#include <debug.h>

#include <parse/parse.h>

#include "possession.h"
#include "implication.h"

struct expression* specialize_implication_expression(
	struct type_cache* tcache,
	struct zebu_implication_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	unsigned i, n = zexpression->implies.n;
	
	if (!n)
	{
		retval = specialize_possession_expression(tcache, zexpression->base);
	}
	else for (i = 0; i < n; i++)
	{
		// they all have be boolean types
		TODO;
	}
	
	EXIT;
	return retval;
}

