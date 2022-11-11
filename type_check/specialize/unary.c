
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "postfix.h"
#include "unary.h"

struct expression* specialize_unary_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_unary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_postfix_expression(tcache, scope, zexpression->base);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

