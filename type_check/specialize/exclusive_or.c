
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "and.h"
#include "exclusive_or.h"

struct expression* specialize_exclusive_or_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_exclusive_or_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_and_expression(tcache, scope, zexpression->base);
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

