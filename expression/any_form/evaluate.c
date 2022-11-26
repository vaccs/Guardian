
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* any_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct any_form_expression* this = (void*) super;
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	assert(list->kind == vk_list);
	
	struct value* value = any_form_run(super->type,
		(struct list_value*) list);
	
	free_value(list);
	
	EXIT;
	return value;
}













