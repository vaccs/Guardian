
#include <debug.h>

#include <value/compare.h>

#include "struct.h"
#include "compare.h"

int compare_value_pairs(const void* a, const void* b)
{
	const struct value_pair *A = a, *B = b;
	
	return compare_values(A->key, B->key);
}

