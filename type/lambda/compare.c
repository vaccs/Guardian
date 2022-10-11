
#include <debug.h>

#include <list/type/compare.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_lambda_types(
	const struct type* super_a,
	const struct type* super_b)
{
	ENTER;
	
	const struct lambda_type *a = (void*) super_a;
	const struct lambda_type *b = (void*) super_b;
	
	int cmp = compare_type_list(a->parameters, b->parameters);
	
	if (!cmp)
	{
		cmp = compare_types(a->rettype, b->rettype);
	}
	
	EXIT;
	return cmp;
}

