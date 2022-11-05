
#include <debug.h>

#include <parse/parse.h>

#include "additive.h"
#include "shift.h"

struct type* determine_type_of_shift_expression(
	struct zebu_shift_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type)
{
	struct type* type;
	ENTER;
	
	if (expression->left)
	{
		TODO;
	}
	else
	{
		type = determine_type_of_additive_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
}

