
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_function_lookup_nodes(const void* a, const void* b)
{
	const struct function_lookup_node *A = a, *B = b;
	
	if (A->type > B->type)
		return +1;
	else if (A->type < B->type)
		return -1;
	else if (A->kind > B->kind)
		return +1;
	else if (A->kind < B->kind)
		return -1;
	
	return +0;
}

