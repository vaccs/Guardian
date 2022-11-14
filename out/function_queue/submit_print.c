
#include <stddef.h>

#include <debug.h>

#include <quack/append.h>

#include <avl/insert.h>
#include <avl/search.h>

#include "funcdata/struct.h"
#include "funcdata/new.h"

#include "struct.h"
#include "submit_print.h"

unsigned function_queue_submit_print(
	struct function_queue* this,
	struct type* type)
{
	unsigned id;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_print,
		.type = type,
	});
	
	if (node)
	{
		struct funcdata* old = node->item;
		id = old->id;
	}
	else
	{
		node = avl_search(this->done, &(struct funcdata) {
			.kind = fk_print,
			.type = type,
		});
		
		if (node)
		{
			struct funcdata* fdata = node->item;
			
			id = fdata->id;
			
			quack_append(this->todo, fdata);
			
			avl_insert(this->queued, fdata);
		}
		else
		{
			struct funcdata* fdata = new_funcdata(fk_print, type, NULL, NULL, id = this->next++);
			
			quack_append(this->todo, fdata);
			
			avl_insert(this->queued, fdata);
		}
	}
	
	EXIT;
	return id;
}

