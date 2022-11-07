
#include <assert.h>
#include <stdio.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void float_value_print(
	struct value* super)
{
	ENTER;
	
	assert(super->kind == vk_float);
	
	struct float_value* spef = (void*) super;
	
	printf("%Lg", spef->value);
	
	EXIT;
}

