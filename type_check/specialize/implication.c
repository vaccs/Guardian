
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "possession.h"
#include "implication.h"

struct expression* specialize_implication_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	TODO;
	#if 0
	if (zexpression->implies)
	{
		TODO;
	}
	else
	{
		retval = specialize_possession_expression(tcache, sshared, zexpression->base);
	}
	
	EXIT;
	return retval;
	#endif
}

