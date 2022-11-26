
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* set_math_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct set_math_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	assert(left->kind == vk_set);
	assert(right->kind == vk_set);
	
	struct value* value;
	switch (this->kind)
	{
		case smek_union:
		{
			value = set_math_union_run(
				super->type,
				(struct set_value*) left,
				(struct set_value*) right);
			break;
		}
		
		case smek_intersect:
		{
			value = set_math_intersect_run(
				super->type,
				(struct set_value*) left,
				(struct set_value*) right);
			break;
		}
		
		case smek_difference:
		{
			value = set_math_difference_run(
				super->type,
				(struct set_value*) left,
				(struct set_value*) right);
			break;
		}
		
		case smek_symdifference:
		{
			value = set_math_symdifference_run(
				super->type,
				(struct set_value*) left,
				(struct set_value*) right);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	free_value(left);
	free_value(right);
	
	EXIT;
	return value;
}

















