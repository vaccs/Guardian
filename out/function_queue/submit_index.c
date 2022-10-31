
#include <debug.h>

#include "funcdata/struct.h"
#include "funcdata/new.h"

#include "struct.h"
#include "submit_inc.h"

unsigned function_queue_submit_index(
	struct function_queue* this,
	struct type* type)
{
	unsigned id;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_index,
		.type = type,
	});
	
	if (node)
	{
		struct funcdata* old = node->item;
		id = old->id;
	}
	else
	{
		struct funcdata* fdata = new_funcdata(fk_index, type, NULL, NULL, id = this->next++);
		
		quack_append(this->todo, fdata);
		
		avl_insert(this->queued, fdata);
	}
	
	EXIT;
	return id;
}

