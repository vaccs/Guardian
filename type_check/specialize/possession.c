
#include <debug.h>

#include <expression/has/new.h>
#include <expression/free.h>

#include <parse/parse.h>

#include "inclusion.h"
#include "possession.h"

struct expression* specialize_possession_expression(
	struct type_cache* tcache,
	struct zebu_possession_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->has)
	{
		struct expression* object = specialize_inclusion_expression(tcache, zexpression->base);
		
		struct string* fieldname = new_string_from_token(zexpression->has);
		
		retval = new_has_expression(tcache, object, fieldname);
		
		free_expression(object);
		
		free_string(fieldname);
	}
	else
	{
		retval = specialize_inclusion_expression(tcache, zexpression->base);
	}
	
	EXIT;
	return retval;
}

