
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "expression.h"

struct expression* specialize_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	retval = specialize_lambda_expression(tcache, sshared, zexpression->base);
	
	EXIT;
	return retval;
}











