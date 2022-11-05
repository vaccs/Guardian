
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "logical_and.h"
#include "logical_or.h"

struct expression* specialize_logical_or_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_logical_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_logical_and_expression(tcache, sshared, zexpression->base);
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

