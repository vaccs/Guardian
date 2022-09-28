
#include <debug.h>

#include <type/free.h>

#include "struct.h"
#include "free.h"

void free_named_type(void* ptr)
{
	ENTER;
	
	struct named_type* this = ptr;
	
	free_string(this->name);
	
	free_type(this->type);
	
	free(this);
	
	EXIT;
}

