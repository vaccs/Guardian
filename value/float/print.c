
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

struct stringtree* float_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == vk_float);
	
	struct float_value* spef = (void*) super;
	
	printf("%Lg", spef->value);
	#endif
	
	EXIT;
}

