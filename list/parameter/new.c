
#include <debug.h>

#include "struct.h"
#include "new.h"

struct parameter_list* new_parameter_list()
{
	ENTER;
	
	struct parameter_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->cap = 0;
	this->n = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

