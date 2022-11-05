
#include <debug.h>

#include <parse/parse.h>

#include "lambda.h"
#include "expression.h"

struct type* determine_type_of_expression(
	struct zebu_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type)
{
	ENTER;
	
	struct type* type = determine_type_of_lambda_expression(expression->base, tcache, grammar_types, name_to_type);
	
	EXIT;
	return type;
}

