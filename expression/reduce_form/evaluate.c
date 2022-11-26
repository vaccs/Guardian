
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* reduce_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct reduce_form_expression* this = (void*) super;
	
	struct value* lambda = expression_evaluate(tcache, this->lambda, environment);
	
	assert(lambda->kind == vk_lambda);
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	assert(list->kind == vk_list);
	
	struct value* initial = expression_evaluate(tcache, this->initial, environment);
	
	struct value* value = reduce_form_run(
		tcache,
		super->type,
		(struct lambda_value*) lambda,
		(struct list_value*) list,
		initial);
	
	free_value(lambda);
	
	free_value(list);
	
	free_value(initial);
	
	EXIT;
	return value;
}













