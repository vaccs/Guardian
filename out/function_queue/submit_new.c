
#include <debug.h>

#include "funcdata/struct.h"
#include "funcdata/new.h"

#include "struct.h"
#include "submit_new.h"

unsigned function_queue_submit_new(
	struct function_queue* this,
	struct type* type)
{
	unsigned id;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_new,
		.type = type,
	});
	
	if (node)
	{
		struct funcdata* fdata = node->item;
		
		id = fdata->id;
	}
	else
	{
		struct funcdata* fdata = new_funcdata(fk_new, type, NULL, id = this->next++);
		
		quack_append(this->todo, fdata);
		
		avl_insert(this->queued, fdata);
	}
	
	EXIT;
	return id;
}

