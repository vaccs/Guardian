
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct raw_statement_list* new_raw_statement_list()
{
	ENTER;
	
	struct raw_statement_list* this = smalloc(sizeof(*this));
	
	this->data = NULL;
	this->n = 0;
	this->cap = 0;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

