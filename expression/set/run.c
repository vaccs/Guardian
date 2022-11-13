
#include <assert.h>
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
			struct value* this = elements->data[i];
			struct value* that = elements->data[i+1];
			
			int cmp = compare_values(this, that);
			
			if (cmp > 0)
			{
				elements->data[i] = that;
				elements->data[i+1] = this;
				changed = true;
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

