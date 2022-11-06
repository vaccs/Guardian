
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct value_list* new_value_list()
{
	ENTER;
	
	struct value_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

