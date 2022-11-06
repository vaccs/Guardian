
#include <assert.h>

#include <debug.h>

#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* comparison_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct comparison_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(this->left, scope);
	struct value* right = expression_evaluate(this->right, scope);
	
	TODO;
	
	free_value(left), free_value(right);
	
	EXIT;
/*	return value;*/
}













