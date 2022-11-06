
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct capture_list* new_capture_list()
{
	ENTER;
	
	struct capture_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	
	this->n = 0;
	
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

