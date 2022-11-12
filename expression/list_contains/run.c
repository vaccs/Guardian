
#include <stdbool.h>

#include <debug.h>

#include <value/compare.h>

#include <value/bool/new.h>

#include <list/value/struct.h>

#include <value/list/struct.h>

#include "run.h"

struct value* list_contains_run(
	struct type* type,
	struct value* element,
	struct list_value* list)
{
	ENTER;
	
	bool found = false;
	
	for (unsigned i = 0, n = list->elements->n; !found && i < n; i++)
	{
		if (!compare_values(element, list->elements->data[i]))
		{
			found = true;
		}
	}
	
	struct value* value = new_bool_value(type, found);
	
	EXIT;
	return value;
}

