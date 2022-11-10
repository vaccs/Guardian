
#include <debug.h>

#include "type_to_id_node.h"

int compare_type_to_id_nodes(const void* a, const void* b)
{
	const struct type_to_id_node* A = a, *B = b;
	if (A->type > B->type)
		return +1;
	else if (A->type < B->type)
		return -1;
	else return 0;
}



