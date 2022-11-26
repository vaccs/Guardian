
#include <assert.h>

#include <errno.h>
#include <stdlib.h>

#include <debug.h>

#include <type_cache/get_float_type.h>

#include <value/free.h>

#include <parse/parse.h>

#include <expression/literal/new.h>

#include <value/float/new.h>

#include "float.h"

struct expression* specialize_primary_float_expression(
	struct type_cache* tcache,
	struct zebu_token* float_literal)
{
	ENTER;
	
	dpvs(float_literal->data);
	
	errno = 0;
	
	char* m;
	
	long double number = strtold((char*) float_literal->data, &m);
	
	if (errno || *m)
	{
		TODO;
		exit(1);
	}
	
	dpv(number);
	
	struct type* type = type_cache_get_float_type(tcache);
	
	struct value* value = new_float_value(type, number);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}


