
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type_cache/get_type/bool.h>

#include "possession.h"
#include "implication.h"

struct type* determine_type_of_implication_expression(
	struct zebu_implication_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->implies)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else
	{
		type = determine_type_of_possession_expression(expression->base, tcache, scope);
	}
	
	EXIT;
	return type;
}

