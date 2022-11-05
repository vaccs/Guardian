
#include <debug.h>

#include "struct.h"
#include "new.h"

struct string_list* new_string_list()
{
	ENTER;
	
	struct string_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

