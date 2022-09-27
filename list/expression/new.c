
#include <debug.h>

#include "struct.h"
#include "new.h"

struct expression_list* new_expression_list()
{
	ENTER;
	
	struct expression_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

