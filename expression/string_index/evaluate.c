
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* string_index_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct string_index_expression* this = (void*) super;
	
	struct value* string = expression_evaluate(tcache, this->string, environment);
	
	assert(string->kind == vk_string);
	
	struct value* index = expression_evaluate(tcache, this->index, environment);
	
	assert(index->kind == vk_int);
	
	struct value* value = string_index_run(super->type,
		(struct string_value*) string,
		(struct int_value*) index);
	
	free_value(string);
	
	free_value(index);
	
	EXIT;
	return value;
}






















