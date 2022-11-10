
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct expression_pair_list* new_expression_pair_list()
{
	ENTER;
	
	struct expression_pair_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

