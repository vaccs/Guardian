
#include <debug.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_set_type(
	const struct type* super_a,
	const struct type* super_b)
{
	ENTER;
	
	const struct set_type *A = (void*) super_a, *B = (void*) super_b;
	
	int cmp = compare_types(A->element_type, B->element_type);
	
	EXIT;
	return cmp;
}

