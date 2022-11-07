
#include <debug.h>

#include <list/type/compare.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_tuple_types(
	const struct type* super_a,
	const struct type* super_b)
{
	ENTER;
	
	const struct tuple_type *a = (void*) super_a;
	const struct tuple_type *b = (void*) super_b;
	
	int cmp = compare_type_list(a->subtypes, b->subtypes);
	
	EXIT;
	return cmp;
}

