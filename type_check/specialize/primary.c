
#include <debug.h>

#include <parse/parser.h>

#include "primary.h"

static struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer)
{
	ENTER;
	
	dpvs(integer->data);
	
	errno = 0;
	
	char* m;
	signed long number = strtol((void*) integer->data, &m, 0);
	
	if (errno || *m)
	{
		TODO;
		exit(1);
	}
	
	dpv(number);
	
	struct value* value = new_integer_value(number);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->integer_literal)
	{
		retval = specialize_primary_integer_expression(tcache, zexpression->integer_literal);
	}
	else if (zexpression->float_literal)
	{
		TODO;
	}
	else if (zexpression->character_literal)
	{
		TODO;
	}
	else if (zexpression->string_literal)
	{
		TODO;
	}
	else if (zexpression->identifier)
	{
		TODO;
	}
	else if (zexpression->tuple)
	{
		TODO;
	}
	else if (zexpression->list)
	{
		TODO;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















