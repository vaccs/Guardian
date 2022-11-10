
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>

#include <pair/value/struct.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_dict_value(
	const struct value* a,
	const struct value* b)
{
	int cmp = 0;
	ENTER;
	
	const struct dict_value* A = (const void*) a;
	const struct dict_value* B = (const void*) b;
	
	struct avl_node_t* an = A->tree->head;
	struct avl_node_t* bn = B->tree->head;
	
	while (!cmp && an && bn)
	{
		struct value_pair *ae = an->item, *be = bn->item;
		
		cmp = compare_values(ae->first, be->first);
		
		an = an->next, bn = bn->next;
	}
	
	if (!cmp)
	{
		if (an)
			cmp = +1;
		else if (bn)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
}














