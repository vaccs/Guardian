
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "let.h"

struct expression* specialize_let_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_let_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_lambda_expression(tcache, sshared, scope, zexpression->base);
	}
	else if (zexpression->let)
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











