
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <list/value/struct.h>

#include <value/bool/struct.h>
#include <value/bool/new.h>

#include <value/list/struct.h>

#include "run.h"

struct value* any_form_run(
	struct type* type,
	struct list_value* list)
{
	ENTER;
	
	bool result = false;
	
	for (unsigned i = 0, n = list->elements->n; !result && i < n; i++)
	{
		struct value* element = list->elements->data[i];
		
		assert(element->kind == vk_bool);
		
		struct bool_value* boolean = (void*) element;
		
		result = boolean->value;
	}
	
	dpvb(result);
	
	struct value* value = new_bool_value(type, result);
	
	EXIT;
	return value;
}













