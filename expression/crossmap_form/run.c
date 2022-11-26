
#include <assert.h>
#include <stdlib.h>

/*#include <memory/smalloc.h>*/

#include <list/value/struct.h>
#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <value/list/struct.h>
#include <value/list/new.h>

/*#include <value/lambda/struct.h>*/
#include <expression/funccall/run.h>
#include <value/free.h>

#include <debug.h>

#include "run.h"

struct value* crossmap_form_run(
	struct type_cache* tcache,
	struct type* type,
	struct lambda_value* lambda,
	struct value_list* args)
{
	ENTER;
	
	assert(args->n >= 1);
	
	unsigned N = args->n;
	
	struct value_list* lambda_args = new_value_list();
	
	for (unsigned i = 0; i < N; i++)
	{
		value_list_append(lambda_args, NULL);
	}
	
	struct value_list* elements = new_value_list();
	
	void helper(unsigned I)
	{
		ENTER;
		
		dpv(I);
		
		if (I < N)
		{
			struct list_value* list = (void*) args->data[I];
			
			for (unsigned i = 0, n = list->elements->n; i < n; i++)
			{
				lambda_args->data[I] = list->elements->data[i];
				helper(I + 1);
			}
			
			lambda_args->data[I] = NULL;
		}
		else
		{
			struct value* result = funccall_run(tcache, lambda, lambda_args);
			
			value_list_append(elements, result);
			
			free_value(result);
		}
		
		EXIT;
	}
	
	helper(0);
	
	struct value* retval = new_list_value(type, elements);
	
	free_value_list(elements);
	
	free_value_list(lambda_args);
	
	EXIT;
	return retval;
}


















