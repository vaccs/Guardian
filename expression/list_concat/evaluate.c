
#include <assert.h>

#include <debug.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* list_concat_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct list_concat_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(tcache, this->left, environment);
	
	struct value* right = expression_evaluate(tcache, this->right, environment);
	
	struct value* value = list_concat_run(
		super->type,
		(struct list_value*) left,
		(struct list_value*) right);
	
	free_value(left);
	
	free_value(right);
	
	EXIT;
	return value;
}
