
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
	
	unsigned i = 0, n = a->n, m = b->n;
	
	while (!cmp && i < n && i < m)
	{
		struct type *ae = a->data[i], *be = b->data[i];
		
		cmp = compare_types(ae, be);
		
		i++;
	}
	
	if (!cmp)
	{
		if (i < n)
			cmp = +1;
		else if (i < m)
			cmp = -1;
	}
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

