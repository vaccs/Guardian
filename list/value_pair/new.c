
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct value_pair_list* new_value_pair_list()
{
	ENTER;
	
	struct value_pair_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

