
#include <assert.h>

#include <debug.h>

/*#include <type/compare.h>*/

/*#include <parameter/struct.h>*/

#include "struct.h"
#include "compare.h"

int compare_parameter_list(
	const struct parameter_list* a,
	const struct parameter_list* b)
{
	int cmp = 0;
	ENTER;
	
	TODO;
	#if 0
	unsigned i = 0, n = a->n, m = b->n;
	
	while (!cmp && i < n && i < m)
	{
		struct parameter *ae = a->data[i], *be = b->data[i];
		
		cmp = compare_types(ae->type, be->type), i++;
	}
	
	if (!cmp)
	{
		if (i < n)
			cmp = +1;
		else if (i < m)
			cmp = -1;
	}
	
	dpv(cmp);
	
	CHECK;
	
	EXIT;
	return cmp;
	#endif
}

