
#include <stdbool.h>

#include <debug.h>

#include <list/value/struct.h>

#include <value/set/new.h>

#include <value/compare.h>

#include "run.h"

struct value* set_run(
	struct type* type,
	struct value_list* elements)
{
	ENTER;
	
	for (bool changed = true; changed; )
	{
		changed = false;
		
		for (unsigned i = 0, n = elements->n - 1; i < n; i++)
		{
			int cmp = compare_values(elements->data[i], elements->data[i+1]);
			
			if (cmp > 0)
			{
				TODO;
			}
			else if (cmp == 0)
			{
				TODO;
			}
		}
	}
	
	struct value* value = new_set_value(type, elements);
	
	EXIT;
	return value;
}

