
#include <debug.h>

#include <named/expression/compare.h>

/*#include <named_expression/struct.h>*/

#include "struct.h"
#include "compare.h"

int compare_named_expression_list(
	const struct named_expression_list* a,
	const struct named_expression_list* b)
{
	int cmp = 0;
	ENTER;
	
	unsigned i = 0, n = a->n, m = b->n;
	
	while (!cmp && i < n && i < m)
	{
		struct named_expression *ae = a->data[i], *be = b->data[i];
		
		cmp = compare_named_expressions(ae, be);
		
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

