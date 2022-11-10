
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct capture_list* inc_capture_list(
	struct capture_list* this)
{
	ENTER;
	
	if (this)
		this->refcount++;
	
	EXIT;
	return this;
}

