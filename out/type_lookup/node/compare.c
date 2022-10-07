
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_type_lookup_nodes(const void* a, const void* b)
{
	const struct type_lookup_node *A = a, *B = b;
	
	if (A->type > B->type)
		return +1;
	else if (A->type < B->type)
		return +1;
	else
		return +0;
}

