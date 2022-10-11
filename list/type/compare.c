
#include <debug.h>

#include <type/compare.h>

#include <type/struct.h>

#include "struct.h"
#include "compare.h"

int compare_type_list(
	const struct type_list* a,
	const struct type_list* b)
{
	int cmp = 0;
	ENTER;
	
	unsigned i = 0, n = a->n;
	unsigned j = 0, m = b->n;
	
	while (!cmp && i < n && j < m)
	{
		struct type* ae = a->data[i];
		struct type* be = a->data[j];
		
		cmp = compare_types(ae, be);
		
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

