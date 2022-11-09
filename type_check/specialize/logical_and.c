
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "inclusive_or.h"
#include "logical_and.h"

struct expression* specialize_logical_and_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_logical_and_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_inclusive_or_expression(tcache, sshared, scope, zexpression->base);
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

