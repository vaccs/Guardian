
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* list_index_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct list_index_expression* this = (void*) super;
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	assert(list->kind == vk_list);
	
	struct value* index = expression_evaluate(tcache, this->index, environment);
	
	assert(index->kind == vk_int);
	
	struct value* value = list_index_run(super->type,
		(struct list_value*) list,
		(struct int_value*) index);
	
	free_value(list);
	free_value(index);
	
	EXIT;
	return value;
}













