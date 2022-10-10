
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_type_queue(struct type_queue* this)
{
	free_quack(this->todo);
	
	free_ptrset(this->queued);
	free_ptrset(this->done);
	
	free_stringtree(this->text);
	
	free(this);
}

