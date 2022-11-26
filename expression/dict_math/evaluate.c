
#include <assert.h>

#include <debug.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* dict_math_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct dict_math_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	struct value* value;
	switch (this->kind)
	{
		case dmek_union:
			value = dict_math_union_run(
				super->type,
				(struct dict_value*) left,
				(struct dict_value*) right);
			break;
		
		case dmek_intersect:
			value = dict_math_intersect_run(
				super->type,
				(struct dict_value*) left,
				(struct dict_value*) right);
			break;
		
		case dmek_difference:
			value = dict_math_difference_run(
				super->type,
				(struct dict_value*) left,
				(struct dict_value*) right);
			break;
		
		case dmek_symdifference:
			value = dict_math_symdifference_run(
				super->type,
				(struct dict_value*) left,
				(struct dict_value*) right);
			break;
		
		default:
			TODO;
			break;
	}
	
	free_value(left);
	free_value(right);
	
	EXIT;
	return value;
}











