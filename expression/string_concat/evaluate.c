
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* string_concat_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct string_concat_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	assert(left->kind == vk_string);
	
	assert(right->kind == vk_string);
	
	struct value* value = string_concat_run(
		super->type,
		(struct string_value*) left,
		(struct string_value*) right);
	
	free_value(left);
	
	free_value(right);
	
	EXIT;
	return value;
}
