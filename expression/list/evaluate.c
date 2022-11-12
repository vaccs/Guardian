
#include <assert.h>

#include <debug.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <list/expression/foreach.h>

#include <value/list/new.h>
#include <value/free.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* list_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_list);
	
	struct list_expression* this = (void*) super;
	
	struct value_list* elements = new_value_list();
	
	expression_list_foreach(this->elements, ({
		void runme(struct expression* expression)
		{
			struct value* value = expression_evaluate(expression, scope);
			
			value_list_append(elements, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* value = new_list_value(super->type, elements);
	
	free_value_list(elements);
	
	EXIT;
	return value;
	#endif
}













