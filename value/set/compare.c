
#include <debug.h>

#include <list/value/compare.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_set_value(
	const struct value* a,
	const struct value* b)
{
	int cmp = 0;
	ENTER;
	
	const struct set_value* A = (const void*) a;
	const struct set_value* B = (const void*) b;
	
	cmp = compare_value_lists(A->elements, B->elements);
	
	EXIT;
	return cmp;
}














