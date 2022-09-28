
#include <debug.h>

#include <value/free.h>

#include "struct.h"
#include "free.h"

void free_named_value(void* ptr)
{
	struct named_value* this = ptr;
	
	free_string(this->name);
	
	free_value(this->value);
	
	free(this);
}

