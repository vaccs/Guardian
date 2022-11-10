
#include <debug.h>

#include <avl/tree.h>

#include <type_check/scope/node/struct.h>

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
		
		struct type_check_scope_node *ae, *be;
		
		while (an && (ae = an->item)->value) an = an->next;
		while (bn && (be = bn->item)->value) bn = bn->next;
		
		while (an && bn)
		{
			int cmp = 0
				?: compare_strings(ae->name, be->name)
				?: compare_types(ae->type, be->type);
			
			if (cmp) return cmp;
			
			do an = an->next; while (an && (ae = an->item)->value);
			do bn = bn->next; while (bn && (be = bn->item)->value);
		}
		
		if (an)
			return +1;
		else if (bn)
			return -1;
		else
			return 0;
	}
}














