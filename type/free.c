
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_type2(struct type* this)
{
	ENTER;
	
	assert(this->inheritance);
	assert(this->inheritance->free);
	
	(this->inheritance->free)(this);
	
	free(this);
	
	EXIT;
}

