
#include <debug.h>

#include <type/compare.h>

#include <parameter/struct.h>

#include "struct.h"
#include "compare.h"

int compare_parameter_list(
	const struct parameter_list* a,
	const struct parameter_list* b)
{
	int cmp = 0;
	ENTER;
	
	unsigned i = 0, n = a->n;
	unsigned j = 0, m = b->n;
	
	while (!cmp && i < n && j < m)
	{
		struct parameter* ae = a->data[i];
		struct parameter* be = a->data[j];
		
		cmp = compare_types(ae->type, be->type);
		
		i++, j++;
	}
	
	if (!cmp)
	{
		if (i < n)
			cmp = +1;
		else if (j < m)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
}

