
#include <stdbool.h>

#include <debug.h>

#include <value/compare.h>

/*#include <value/bool/new.h>*/

/*#include <dict/value/struct.h>*/

#include <value/bool/new.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>

#include <value/dict/struct.h>

#include "run.h"

struct value* dict_contains_run(
	struct type* type,
	struct value* element,
	struct dict_value* dict)
{
	ENTER;
	
	struct value_pair_list* array = dict->elements;
	
	signed l = 0, r = array->n - 1;
	
	bool found = false;
	
	while (!found && r >= l)
	{
		dpv(l);
		dpv(r);
		
		int mid = l + (r - l) / 2;
		
		int cmp = compare_values(array->data[mid]->key, element);
		
		if (cmp > 0)
			r = mid - 1;
		else if (cmp < 0)
			l = mid + 1;
		else
			found = true;
	}
	
	struct value* value = new_bool_value(type, found);
	
	EXIT;
	return value;
}

















