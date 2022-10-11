
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_list_type(
	struct type* super)
{
	ENTER;
	
	struct list_type* this = (void*) super;
	
	EXIT;
}

