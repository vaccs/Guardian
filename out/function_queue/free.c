
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_function_queue(struct function_queue* this)
{
	ENTER;
	
	free_quack(this->todo);
	
	avl_free_tree(this->queued);
	
	avl_free_tree(this->done);
	
	free_stringtree(this->text);
	
	free(this);
	
	EXIT;
}

