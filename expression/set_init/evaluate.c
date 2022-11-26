
#include <assert.h>

#include <debug.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <list/expression/foreach.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* set_init_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_set_init);
	
	struct set_init_expression* this = (void*) super;
	
	struct value_list* elements = new_value_list();
	
	expression_list_foreach(this->elements, ({
		void runme(struct expression* expression)
		{
			struct value* value = expression_evaluate(tcache, expression, environment);
			
			value_list_append(elements, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* value = set_init_run(super->type, elements);
	
	free_value_list(elements);
	
	EXIT;
	return value;
}













