
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <value/free.h>
#include <value/struct.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* list_slice_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct list_slice_expression* this = (void*) super;
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	assert(list->kind == vk_list);
	
	struct value* startindex = NULL;
	
	struct value* endindex = NULL;
	
	if (this->startindex)
	{
		startindex = expression_evaluate(tcache, this->startindex, environment);
		assert(startindex->kind == vk_int);
	}
	
	if (this->endindex)
	{
		endindex = expression_evaluate(tcache, this->endindex, environment);
		assert(endindex->kind == vk_int);
	}
	
	struct value* value = list_slice_run(super->type,
		(struct list_value*) list,
		(struct int_value*) startindex,
		(struct int_value*) endindex);
	
	free_value(list);
	
	free_value(startindex);
	
	free_value(endindex);
	
	EXIT;
	return value;
}













