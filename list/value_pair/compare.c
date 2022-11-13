
#include <debug.h>

#include <value/compare.h>

#include <pair/value/struct.h>

#include "struct.h"
#include "compare.h"

int compare_value_pair_lists(
	const struct value_pair_list* a,
	const struct value_pair_list* b)
{
	int cmp = 0;
	ENTER;
	
	unsigned i = 0, a_n = a->n, b_n = b->n;
	
	while (!cmp && i < a_n && i < b_n)
	{
		struct value_pair* ae = a->data[i];
		struct value_pair* be = b->data[i];
		
		cmp = compare_values(ae->key, be->key);
		
		i++;
	}
	
	if (!cmp)
	{
		if (a_n > b_n)
			cmp = +1;
		else if (a_n < b_n)
			cmp = -1;
	}
	
	EXIT;
	return cmp;

}


