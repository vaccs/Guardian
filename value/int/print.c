
#include <assert.h>
#include <gmp.h>

#include <debug.h>

#include "struct.h"
#include "print.h"

struct stringtree* int_value_print(
	struct value* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct int_value* spef = (void*) super;
	
	gmp_printf("%Zi", spef->value);
	#endif
	
	EXIT;
}

