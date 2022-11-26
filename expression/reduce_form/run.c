
#include <debug.h>

#include <assert.h>
#include <stdlib.h>

/*#include <memory/smalloc.h>*/

/*#include <list/value/struct.h>*/
/*#include <list/value/new.h>*/
/*#include <list/value/append.h>*/
/*#include <list/value/free.h>*/

/*#include <value/list/struct.h>*/
/*#include <value/list/new.h>*/

/*#include <value/lambda/struct.h>*/
/*#include <expression/funccall/run.h>*/
/*#include <value/free.h>*/

/*#include <debug.h>*/

#include "run.h"

struct value* reduce_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct value_list* args)
{
	ENTER;
	
	TODO;
	#if 0
	assert(args->n >= 1);
	
	unsigned n = args->n, m = -1;
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* generic = args->data[i];
		
		assert(generic->kind == vk_list);
		
		struct list_value* list = (void*) generic;
		
		if (list->elements->n < m)
			m = list->elements->n;
	}
	
	dpv(m);
	
	struct value_list* elements = new_value_list();
	
	for (unsigned j = 0; j < m; j++)
	{
		struct value_list* call_args = new_value_list();
		
		for (unsigned i = 0; i < n; i++)
		{
			struct list_value* list = (void*) args->data[i];
			
			value_list_append(call_args, list->elements->data[j]);
		}
		
		struct value* result = funccall_run(tcache, lambda, call_args);
		
		value_list_append(elements, result);
		
		free_value(result);
		
		free_value_list(call_args);
	}
	
	struct value* retval = new_list_value(type, elements);
	
	free_value_list(elements);
	
	EXIT;
	return retval;
	#endif
}


















