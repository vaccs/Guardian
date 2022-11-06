
#include <stdlib.h>

#include <debug.h>

#include <stringtree/free.h>

#include <set/ptr/free.h>

#include <quack/free.h>

#include "struct.h"
#include "free.h"

void free_type_queue(struct type_queue* this)
{
	ENTER;
	
	free_quack(this->todo);
	
	free_ptrset(this->queued);
	free_ptrset(this->done);
	
	free_stringtree(this->text);
	
	free(this);
	
	EXIT;
}

