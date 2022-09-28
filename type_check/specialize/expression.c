
#include <debug.h>

#include <parse/parse.h>

#include "implication.h"
#include "expression.h"

struct expression* specialize_expression(
	struct type_cache* tcache,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	unsigned i, n = zexpression->iffs.n;
	
	if (!n)
	{
		retval = specialize_implication_expression(tcache, zexpression->base);
	}
	else for (i = 0; i < n; i++)
	{
		// they all have be boolean types
		TODO;
	}
	
	EXIT;
	return retval;
}











