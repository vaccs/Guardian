
#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <value/inc.h>

#include <list/value/foreach.h>

#include <value/list/struct.h>

#include <list/value/append.h>
#include <list/value/free.h>
#include <list/value/foreach.h>
#include <list/value/new.h>

#include <expression/funccall/run.h>

#include <value/free.h>

#include "run.h"

struct value* reduce_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct list_value* list,
	struct value* initial)
{
	ENTER;
	
	struct value* result = inc_value(initial);
	
	value_list_foreach(list->elements, ({
		void runme(struct value* element)
		{
			struct value_list* call_args = new_value_list();
			
			value_list_append(call_args, result);
			
			value_list_append(call_args, element);
			
			struct value* new_result = funccall_run(tcache, lambda, call_args);
			
			assert(result->type == new_result->type);
			
			free_value_list(call_args);
			
			free_value(result);
			
			result = new_result;
		}
		runme;
	}));
	
	EXIT;
	return result;
}


















