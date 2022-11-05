
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void list_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_list);
	
	struct list_type* this = (void*) super;
	
	type_print(this->element_type);
	
	printf("[]");
	
	EXIT;
}

