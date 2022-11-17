
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_type_print(
	struct type* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == tk_dict);
	
	struct dict_type* this = (void*) super;
	
	printf("(");
	
	type_print(this->key);
	
	printf(" -> ");
	
	type_print(this->value);
	
	printf(")");
	#endif
	
	EXIT;
}

