
#include <debug.h>

#include <avl/tree.h>

#include <named/type/struct.h>

#include <string/compare.h>

#include <type/compare.h>

#include "struct.h"
#include "compare.h"

int compare_environment_types(
	const struct type* a,
	const struct type* b)
{
	const struct environment_type *A = (void*) a, *B = (void*) b;
	
	if (A->prev > B->prev)
		return +1;
	else if (A->prev < B->prev)
		return -1;
	else
	{
		struct avl_node_t *an = A->variables->head, *bn = B->variables->head;
		
		while (an && bn)
		{
			struct named_type *ae = an->item, *be = bn->item;
		
			int cmp = 0
				?: compare_strings(ae->name, be->name)
				?: compare_types(ae->type, be->type);
			
			if (cmp) return cmp;
			
			an = an->next, bn = bn->next;
		}
		
		if (an)
			return +1;
		else if (bn)
			return -1;
			
		return 0;
	}
}














