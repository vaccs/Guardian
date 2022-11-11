
#if 0

#include <assert.h>
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <list/value/struct.h>
#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <value/list/struct.h>
#include <value/list/new.h>

#include <value/lambda/struct.h>
#include <value/lambda/call.h>
#include <value/free.h>

#include "evaluate.h"

struct value* builtin_map_evaluate(
	struct type* type,
	struct value* generic_lambda,
	struct value_list* args)
{
	ENTER;
	
	assert(args->n >= 1);
	
	assert(generic_lambda->kind == vk_lambda);
	
	struct lambda_value* lambda = (void*) generic_lambda;
	
	unsigned N = args->n;
	
	dpv(N);
	
	struct value_list** lists = smalloc(sizeof(*lists) * N);
	
	struct value_list* lambda_args = new_value_list();
	
	for (unsigned i = 0; i < N; i++)
	{
		struct value* generic_list = args->data[i];
		
		assert(generic_list->kind == vk_list);
		
		struct list_value* list = (void*) generic_list;
		
		lists[i] = list->elements;
		
		value_list_append(lambda_args, NULL);
	}
	
	struct value_list* elements = new_value_list();
	
	void helper(unsigned I)
	{
		ENTER;
		
		dpv(I);
		
		if (I < N)
		{
			struct value_list* list = lists[I];
			
			for (unsigned i = 0, n = list->n; i < n; i++)
			{
				lambda_args->data[I] = list->data[i];
				helper(I + 1);
			}
			
			lambda_args->data[I] = NULL;
		}
		else
		{
			struct value* result = lambda_value_call(lambda, lambda_args);
			
			value_list_append(elements, result);
			
			free_value(result);
		}
		
		EXIT;
	}
	
	helper(0);
	
	struct value* retval = new_list_value(type, elements);
	
	free_value_list(elements);
	
	free_value_list(lambda_args);
	
	free(lists);
	
	EXIT;
	return retval;
}



















#endif
