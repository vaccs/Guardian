
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void dict_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_dict);
	
	struct dict_type* this = (void*) super;
	
	printf("(");
	
	type_print(this->key);
	
	printf(" -> ");
	
	type_print(this->value);
	
	printf(")");
	
	EXIT;
}

