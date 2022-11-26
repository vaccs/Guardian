
#include <assert.h>

#include <debug.h>

#include <value/bool/struct.h>
#include <value/struct.h>
#include <value/bool/new.h>
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* bool_not_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_bool_not);
	
	struct bool_not_expression* this = (void*) super;
	
	struct value* subvalue = expression_evaluate(tcache, this->subexpression, environment);
	
	assert(subvalue->kind == vk_bool);
	
	struct value* value = new_bool_value(super->type, !((struct bool_value*) subvalue)->value);
	
	free_value(subvalue);
	
	EXIT;
	return value;
}
