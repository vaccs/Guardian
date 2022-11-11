
#include <debug.h>

#include <parse/parse.h>

#include "let.h"
#include "expression.h"

struct expression* specialize_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	retval = specialize_let_expression(tcache, scope, zexpression->base);
	
	EXIT;
	return retval;
}











