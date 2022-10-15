
#include <debug.h>

#include <parse/parse.h>

#include "implication.h"
#include "expression.h"

struct expression* specialize_expression(
	struct type_cache* tcache,
	struct zebu_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	retval = specialize_implication_expression(tcache, zexpression);
	
	EXIT;
	return retval;
}











