
#include <assert.h>
#include <stddef.h>
#include <debug.h>

/*#include <dict/value/struct.h>*/
/*#include <dict/value/new.h>*/
/*#include <dict/value/extend.h>*/
/*#include <dict/value/free.h>*/

/*#include <value/dict/struct.h>*/
/*#include <value/dict/new.h>*/

/*#include <mpz/struct.h>*/

/*#include <value/inc.h>*/
/*#include <value/int/struct.h>*/

#include <value/compare.h>
#include <value/inc.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>

#include <value/dict/struct.h>

#include "run.h"

struct value* dict_index_run(
	struct type* type,
	struct dict_value* dict,
	struct value* key)
{
	ENTER;
	
	struct value_pair_list* array = dict->elements;
	
	signed l = 0, r = array->n - 1;
	
	struct value* value = NULL;
	
	while (!value && r >= l)
	{
		dpv(l);
		dpv(r);
		
		int mid = l + (r - l) / 2;
		
		int cmp = compare_values(array->data[mid]->key, key);
		
		if (cmp > 0)
			r = mid - 1;
		else if (cmp < 0)
			l = mid + 1;
		else
			value = inc_value(array->data[mid]->value);
	}
	
	if (!value)
	{
		TODO;
	}
	
	EXIT;
	return value;
}















