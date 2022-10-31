
#include <debug.h>

#include <parse/parse.h>

#include "unary.h"
#include "exponentiation.h"

struct expression* specialize_exponentiation_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_exponentiation_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_unary_expression(tcache, sshared, zexpression->base);
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

