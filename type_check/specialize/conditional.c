
#include <debug.h>

#include <parse/parser.h>

#include "logical_or.h"
#include "conditional.h"

struct expression* specialize_conditional_expression(
	struct type_cache* tcache,
	struct zebu_conditional_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->true_case)
	{
		TODO;
	}
	else
	{
		retval = specialize_logical_or_expression(tcache, zexpression->base);
	}
	
	EXIT;
	return retval;
}

