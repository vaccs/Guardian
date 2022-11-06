
#include <assert.h>

#include <debug.h>

/*#include <expression/has/new.h>*/
/*#include <expression/free.h>*/

#include <parse/parse.h>

#include "logical_or.h"
#include "inclusion.h"

struct expression* specialize_inclusion_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_inclusion_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->list)
	{
		TODO;
	}
	else
	{
		retval = specialize_logical_or_expression(tcache, sshared, zexpression->base);
	}
	
	EXIT;
	return retval;
}

