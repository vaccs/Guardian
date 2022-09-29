
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_id_to_token_nodes(const void* a, const void* b)
{
	int cmp = 0;
	const struct id_to_token_node *A = a, *B = b;
	ENTER;
	
	if (A->id > B->id)
		cmp = +1;
	else if (A->id < B->id)
		cmp = -1;
	
	EXIT;
	return cmp;
}

