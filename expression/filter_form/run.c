
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>
#include <list/value/foreach.h>

#include <value/bool/struct.h>

#include <value/free.h>

#include <value/list/new.h>
#include <value/list/struct.h>

#include <expression/funccall/run.h>

#include "run.h"

struct value* filter_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct list_value* list)
{
	ENTER;
	
	struct value_list* elements = new_value_list();
	
	value_list_foreach(list->elements, ({
		void runme(struct value* element)
		{
			struct value_list* call_args = new_value_list();
			
			value_list_append(call_args, element);
			
			struct value* result = funccall_run(tcache, lambda, call_args);
			
			assert(result->kind == vk_bool);
			
			if (((struct bool_value*) result)->value)
			{
				value_list_append(elements, element);
			}
			
			free_value(result);
			
			free_value_list(call_args);
		}
		runme;
	}));
	
	struct value* retval = new_list_value(type, elements);
	
	free_value_list(elements);
	
	EXIT;
	return retval;
}


















