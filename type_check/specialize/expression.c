
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "expression.h"

struct expression* specialize_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	TODO;
	#if 0
	retval = specialize_lambda_expression(tcache, sshared, scope, zexpression->base);
	
	EXIT;
	return retval;
	#endif
}











