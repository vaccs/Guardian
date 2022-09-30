
#include <debug.h>

#include "struct.h"
#include "print.h"

void integer_value_print(
	struct value* super)
{
	ENTER;
	
	struct integer_value* spef = (void*) super;
	
	gmp_printf("%Zi", spef->integer);
	
	EXIT;
}

