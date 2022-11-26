
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* range_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_range_form);
	
	struct range_form_expression* this = (void*) super;
	
	struct value* start = NULL;
	
	if (this->start)
	{
		start = expression_evaluate(tcache, this->start, environment);
	}
	
	struct value* end = expression_evaluate(tcache, this->end, environment);
	
	assert(start->kind == vk_int);
	assert(end->kind == vk_int);
	
	struct value* result = range_form_run(
		(struct list_type*) super->type,
		(struct int_value*) start,
		(struct int_value*) end);
	
	free_value(start);
	
	free_value(end);
	
	EXIT;
	return result;
}













