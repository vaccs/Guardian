
#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <type_cache/get_bool_type.h>

#include <expression/has/new.h>
#include <expression/free.h>

#include <parse/parse.h>

#include "inclusion.h"
#include "possession.h"

struct expression* specialize_possession_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_possession_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->has)
	{
		struct type* type = type_cache_get_bool_type(tcache);
		
		struct expression* object = specialize_inclusion_expression(tcache, scope, zexpression->base);
		
		struct string* fieldname = new_string_from_token(zexpression->has);
		
		retval = new_has_expression(type, object, fieldname);
		
		free_expression(object);
		
		free_string(fieldname);
	}
	else
	{
		retval = specialize_inclusion_expression(tcache, scope, zexpression->base);
	}
	
	EXIT;
	return retval;
}

