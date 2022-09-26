
#include <debug.h>

#include <parse/parser.h>

#include "shift.h"
#include "relational.h"

struct expression* specialize_relational_expression(
	struct type_cache* tcache,
	struct zebu_relational_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_shift_expression(tcache, zexpression->base);
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

