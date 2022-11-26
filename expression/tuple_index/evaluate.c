
#include <assert.h>

#include <debug.h>

#include <value/tuple/struct.h>

#include <list/value/struct.h>

#include <value/free.h>

#include <value/inc.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* tuple_index_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct tuple_index_expression* this = (void*) super;
	
	struct value* tuple = expression_evaluate(tcache, this->tuple, environment);
	
	assert(tuple->kind == vk_tuple);
	
	struct value* value = inc_value(((struct tuple_value*) tuple)->subvalues->data[this->index]);
	
	free_value(tuple);
	
	EXIT;
	return value;
}























