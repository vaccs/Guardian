
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include "multiplicative.h"
#include "additive.h"

struct type* determine_type_of_additive_expression(
	struct zebu_additive_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type)
{
	struct type* type;
	ENTER;
	
	if (expression->left)
	{
		struct type* left = determine_type_of_additive_expression(
			expression->left, tcache, grammar_types, name_to_type);
		
		struct type* right = determine_type_of_multiplicative_expression(
			expression->right, tcache, grammar_types, name_to_type);
		
		if (left != right)
		{
			// "bad types for add!"
			TODO;
			exit(1);
		}
		
		type = left;
	}
	else
	{
		type = determine_type_of_multiplicative_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	
	EXIT;
	return type;
}

