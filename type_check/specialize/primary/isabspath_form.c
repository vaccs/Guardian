
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <type_cache/get_bool_type.h>

#include <expression/free.h>

#include <expression/isabspath_form/new.h>

#include <expression/struct.h>

#include <type_cache/get_string_type.h>

#include "../expression.h"

#include "isabspath_form.h"

struct expression* specialize_primary_isabspath_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* path = specialize_expression(tcache, scope, raw_argument);
	
	if (path->type != type_cache_get_string_type(tcache))
	{
		TODO;
		exit(1);
	}
	
	struct type* type = type_cache_get_bool_type(tcache);
	
	retval = new_isabspath_form_expression(type, path);
	
	free_expression(path);
	
	EXIT;
	return retval;
}

