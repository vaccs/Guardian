
#include <assert.h>
#include <stdbool.h>

#include <debug.h>

#include <value/dict/new.h>

#include <value/compare.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>

#include "run.h"

struct value* dict_init_run(
	struct type* type,
	struct value_pair_list* elements)
{
	ENTER;
	
	for (bool changed = true; changed; )
	{
		changed = false;
		
		for (unsigned i = 0, n = elements->n - 1; i < n; i++)
		{
			struct value_pair* this = elements->data[i];
			struct value_pair* that = elements->data[i + 1];
			
			int cmp = compare_values(this->key, that->key);
			
			if (cmp > 0)
			{
				elements->data[i] = that;
				elements->data[i + 1] = this;
				
				changed = true;
			}
			else if (cmp == 0)
			{
				TODO;
			}
		}
	}
	
	struct value* value = new_dict_value(type, elements);
	
	EXIT;
	return value;
}













