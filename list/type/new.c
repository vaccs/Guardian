
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct type_list* new_type_list()
{
	ENTER;
	
	struct type_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

