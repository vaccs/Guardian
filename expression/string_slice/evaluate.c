
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* string_slice_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct string_slice_expression* this = (void*) super;
	
	struct value* string = expression_evaluate(tcache, this->string, environment);
	
	assert(string->kind == vk_string);
	
	struct value* startindex = NULL;
	struct value* endindex = NULL;
	
	if (this->startindex)
	{
		startindex = expression_evaluate(tcache, this->startindex, environment);
	}
	
	if (this->endindex)
	{
		endindex = expression_evaluate(tcache, this->endindex, environment);
	}
	
	struct value* value = string_slice_run(super->type,
		(struct string_value*) string,
		(struct int_value*) startindex,
		(struct int_value*)   endindex);
	
	free_value(string);
	free_value(startindex);
	free_value(endindex);
	
	EXIT;
	return value;
}













