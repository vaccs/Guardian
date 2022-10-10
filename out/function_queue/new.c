
#include <debug.h>

#include "funcdata/compare.h"

#include "struct.h"
#include "new.h"

struct function_queue* new_function_queue()
{
	ENTER;
	
	struct function_queue* this = smalloc(sizeof(*this));
	
	this->todo = new_quack();
	
	this->queued = avl_alloc_tree(compare_funcdata, NULL);
	
	this->done = avl_alloc_tree(compare_funcdata, free);
	
	this->next = 1;
	
	EXIT;
	return this;
}

