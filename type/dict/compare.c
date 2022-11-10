
#include <debug.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_dict_type(
	const struct type* super_a,
	const struct type* super_b)
{
	const struct dict_type *A = (void*) super_a, *B = (void*) super_b;
	
	return 0
		?: compare_types(A->key, B->key)
		?: compare_types(A->value, B->value);
}

