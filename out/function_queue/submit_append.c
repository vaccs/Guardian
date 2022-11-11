
#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <quack/append.h>

#include <avl/insert.h>
#include <avl/search.h>

#include <type/struct.h>

#include "funcdata/struct.h"
#include "funcdata/new.h"

#include "struct.h"
#include "submit_append.h"

unsigned function_queue_submit_append(
	struct function_queue* this,
	struct type* type)
{
	unsigned id;
	ENTER;
	
	assert(type->kind == tk_list);
	
	struct avl_node_t* node = avl_search(this->queued, &(struct funcdata) {
		.kind = fk_append,
		.type = type,
	});
	
	if (node)
	{
		struct funcdata* fdata = node->item;
		id = fdata->id;
	}
	else
	{
		node = avl_search(this->done, &(struct funcdata) {
			.kind = fk_append,
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
			struct funcdata* fdata = new_funcdata(fk_append, type, NULL, NULL, id = this->next++);
			
			quack_append(this->todo, fdata);
			
			avl_insert(this->queued, fdata);
		}
	}
	
	EXIT;
	return id;
}













