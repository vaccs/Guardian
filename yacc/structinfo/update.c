
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>
#include <avl/insert.h>

#include <string/compare.h>

#include "node/struct.h"
#include "node/inc.h"

#include "struct.h"
#include "update.h"

void structinfo_update(
	struct structinfo* this,
	const struct structinfo* other)
{
	ENTER;
	
	struct avl_node_t* an = this->tree->head, *bn = other->tree->head;
	
	while (an && bn)
	{
		struct structinfo_node *ae = an->item, *be = bn->item;
		
		int cmp = compare_strings(ae->name, be->name);
		
		if (cmp < 0)
		{
			an = an->next;
		}
		else if (cmp > 0)
		{
			avl_insert(this->tree, inc_structinfo_node(be));
			bn = bn->next;
		}
		else if (ae->type != be->type)
		{
			TODO;
			exit(1);
		}
		else
		{
			an = an->next, bn = bn->next;
		}
	}
	
	while (bn)
	{
		struct structinfo_node* be = bn->item;
		avl_insert(this->tree, inc_structinfo_node(be));
		bn = bn->next;
	}
	
	EXIT;
}










