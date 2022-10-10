
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_out_functions(const void* a, const void* b)
{
	const struct out_function *A = a, *B = b;
	
	if (A->rank > B->rank)
		return +1;
	else if (A->rank < B->rank)
		return -1;
	return 0;
}

