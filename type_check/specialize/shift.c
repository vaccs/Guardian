
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "additive.h"
#include "shift.h"

struct expression* specialize_shift_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_shift_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_additive_expression(tcache, scope, zexpression->base);
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

