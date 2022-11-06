
#include <debug.h>

#include "struct.h"
#include "new.h"

struct assertion_list* new_assertion_list()
{
	ENTER;
	
	struct assertion_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

