
#include <debug.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_list_type(
	const struct type* super_a,
	const struct type* super_b)
{
	const struct list_type *A = (void*) super_a, *B = (void*) super_b;
	
	return compare_types(A->element_type, B->element_type);
}

