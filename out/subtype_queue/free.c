
#include <stdlib.h>

#include <debug.h>

#include <stringtree/free.h>

#include <set/ptr/free.h>

#include <quack/free.h>

#include "struct.h"
#include "free.h"

void free_subtype_queue(struct subtype_queue* this)
{
	ENTER;
	
	free_quack(this->values.todo);
	
	free_ptrset(this->values.queued);
	free_ptrset(this->values.done);
	
	free_quack(this->expressions.todo);
	
	free_ptrset(this->expressions.queued);
	free_ptrset(this->expressions.done);
	
	free_stringtree(this->text);
	
	free(this);
	
	EXIT;
}

