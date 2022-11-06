
#include <debug.h>

#include "struct.h"
#include "new.h"

struct declaration_list* new_declaration_list()
{
	ENTER;
	
	struct declaration_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

