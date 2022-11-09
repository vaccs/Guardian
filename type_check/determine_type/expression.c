
#include <debug.h>

#include <parse/parse.h>

#include "let.h"
#include "expression.h"

struct type* determine_type_of_expression(
	struct zebu_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	ENTER;
	
	struct type* type = determine_type_of_let_expression(expression->base, tcache, scope);
	
	EXIT;
	return type;
}

