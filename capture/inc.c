
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct capture* inc_capture(
	struct capture* this)
{
	ENTER;
	
	if (this)
		this->refcount++;
	
	EXIT;
	return this;
}

