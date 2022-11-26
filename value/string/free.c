
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_string_value(
	struct value* super)
{
	ENTER;
	
	struct string_value* this = (void*) super;
	
	free(this->chars);
	
	EXIT;
}

