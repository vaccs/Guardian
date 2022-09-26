
#include <debug.h>

#include <parse/parser.h>

#include "primary.h"
#include "postfix.h"

struct expression* specialize_postfix_expression(
	struct type_cache* tcache,
	struct zebu_postfix_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_primary_expression(tcache, zexpression->base);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

