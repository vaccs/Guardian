
#include <assert.h>

#include <debug.h>

/*#include <avl/free_tree.h>*/

/*#include <string/compare.h>*/

#include "node/struct.h"
#include "node/compare.h"

#include "struct.h"
#include "compare.h"

int compare_structinfos(
	const struct structinfo* a,
	const struct structinfo* b)
{
	TODO;
	#if 0
	int cmp = 0;
	ENTER;
	
	struct avl_node_t* an = a->tree->head, *bn = b->tree->head;
	
	while (!cmp && an && bn)
	{
		struct structinfo_node *ae = an->item, *be = bn->item;
		
		cmp = compare_strings(ae->name, be->name);
		
		if (!cmp)
		{
			if (ae->type > be->type)
				cmp = +1;
			else if (ae->type < be->type)
				cmp = -1;
			else
			{
				an = an->next;
				bn = bn->next;
			}
		}
	}
	
	if (!cmp)
	{
		if (an && !bn)
			cmp = +1;
		else if (!an && bn)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
	#endif
}

