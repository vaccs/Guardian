
#include <debug.h>

#include <parse/parse.h>

#include "and.h"
#include "exclusive_or.h"

struct expression* specialize_exclusive_or_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_exclusive_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_and_expression(tcache, sshared, zexpression->base);
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

