
#include <debug.h>

#include "struct.h"
#include "new.h"

struct stringtree* new_stringtree()
{
	ENTER;
	
	struct stringtree* this = smalloc(sizeof(*this));
	
	this->head = this->tail = NULL;
	
	EXIT;
	return this;
}

