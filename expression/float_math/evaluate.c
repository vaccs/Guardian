
#include <math.h>
#include <quadmath.h>

#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include <value/float/struct.h>
#include <value/float/new.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* float_math_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct float_math_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	assert(left->kind == vk_float);
	assert(right->kind == vk_float);
	
	struct float_value* spef_left = (void*) left;
	struct float_value* spef_right = (void*) right;
	
	__float128 number;
	
	switch (this->kind)
	{
		case fmek_negate:
			TODO;
			break;
		
		case fmek_add:
			number = spef_left->value + spef_right->value;
			break;
		
		case fmek_subtract:
			number = spef_left->value - spef_right->value;
			break;
		
		case fmek_multiply:
			number = spef_left->value * spef_right->value;
			break;
		
		case fmek_qdivide:
			number = spef_left->value / spef_right->value;
			break;
		
		case fmek_rdivide:
			number = fmodq(spef_left->value, spef_right->value);
			break;
		
		case fmek_expo:
			number = powq(spef_left->value, spef_right->value);
			break;
		
		default:
			TODO;
			break;
	}
	
	struct value* value = new_float_value(super->type, number);
	
	free_value(left), free_value(right);
	
	EXIT;
	return value;
}













