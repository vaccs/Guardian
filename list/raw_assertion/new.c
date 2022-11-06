
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct raw_assertion_list* new_raw_assertion_list()
{
	ENTER;
	
	struct raw_assertion_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

