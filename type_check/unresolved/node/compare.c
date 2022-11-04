
#include <debug.h>

#include <string/compare.h>

#include "struct.h"
#include "compare.h"

int compare_unresolved_nodes(const void* a, const void* b)
{
	const struct unresolved_node *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

