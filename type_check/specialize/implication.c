
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "possession.h"
#include "implication.h"

struct expression* specialize_implication_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_implication_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->implies)
	{
		TODO;
	}
	else
	{
		retval = specialize_possession_expression(tcache, sshared, scope, zexpression->base);
	}
	
	EXIT;
	return retval;
}

