
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct stringtree* new_stringtree()
{
	ENTER;
	
	struct stringtree* this = smalloc(sizeof(*this));
	
	this->head = this->tail = NULL;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

