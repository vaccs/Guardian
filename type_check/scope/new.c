
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

struct type_check_scope* new_type_check_scope()
{
	ENTER;
	
	struct type_check_scope* this = smalloc(sizeof(*this));
	
	this->head = NULL;
	
	EXIT;
	return this;
}

