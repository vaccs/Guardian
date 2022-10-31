
#include <debug.h>

#include <parse/parse.h>

#include "equality.h"
#include "and.h"

struct expression* specialize_and_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_and_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_equality_expression(tcache, sshared, zexpression->base);
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

