
#include <debug.h>

/*#include <expression/has/new.h>*/
/*#include <expression/free.h>*/

#include <parse/parse.h>

#include "lambda.h"
#include "inclusion.h"

struct expression* specialize_inclusion_expression(
	struct type_cache* tcache,
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
		retval = specialize_lambda_expression(tcache, zexpression->base);
	}
	
	EXIT;
	return retval;
}

