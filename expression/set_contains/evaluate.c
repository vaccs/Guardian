
#include <assert.h>

#include <debug.h>

#include <value/set/struct.h>
#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* set_contains_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_set_contains);
	
	struct set_contains_expression* this = (void*) super;
	
	struct value* element = expression_evaluate(tcache, this->element, environment);
	
	struct value* set = expression_evaluate(tcache, this->set, environment);
	
	assert(set->kind == vk_set);
	
	struct value* value = set_contains_run(
		super->type,
		element,
		(struct set_value*) set);
	
	free_value(element);
	
	free_value(set);
	
	EXIT;
	return value;
}
