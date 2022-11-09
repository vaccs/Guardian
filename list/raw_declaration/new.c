
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct raw_declaration_list* new_raw_declaration_list()
{
	ENTER;
	
	struct raw_declaration_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	EXIT;
	return this;
}

