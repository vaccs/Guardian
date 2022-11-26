
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* list_contains_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_list_contains);
	
	struct list_contains_expression* this = (void*) super;
	
	struct value* element = expression_evaluate(tcache, this->element, environment);
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	assert(list->kind == vk_list);
	
	struct value* value = list_contains_run(
		super->type,
		element,
		(struct list_value*) list);
	
	free_value(element);
	
	free_value(list);
	
	EXIT;
	return value;
}
