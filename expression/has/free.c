
#include <assert.h>

#include <debug.h>

#include <string/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_has_expression(
	struct expression* super)
{
	ENTER;
	
	struct has_expression* this = (void*) super;
	
	free_expression(this->object);
	
	free_string(this->fieldname);
	
	EXIT;
}

