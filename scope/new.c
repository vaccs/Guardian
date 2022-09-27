
#include <debug.h>

#include "struct.h"
#include "new.h"

struct scope* new_scope()
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	EXIT;
	return this;
}

