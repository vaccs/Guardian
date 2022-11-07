
#include <gmp.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

void int_value_print(
	struct value* super)
{
	ENTER;
	
	struct int_value* spef = (void*) super;
	
	gmp_printf("%Zi", spef->integer);
	
	EXIT;
}

