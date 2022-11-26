
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/bool/struct.h>
#include <value/bool/new.h>
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* implication_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct implication_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	
	assert(left->kind == vk_bool);
	
	if (((struct bool_value*) left)->value)
	{
		free_value(left);
		
		struct value* right = expression_evaluate(tcache, this->right, environment);
		
		assert(right->kind == vk_bool);
		
		EXIT;
		return right;
	}
	else
	{
		free_value(left);
		
		left = new_bool_value(super->type, true);
	}
	
	EXIT;
	return left;
}
