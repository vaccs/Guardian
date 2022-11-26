
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <type_cache/get_bool_type.h>
#include <type_cache/get_string_type.h>

#include <expression/free.h>

#include <expression/struct.h>

#include <expression/isexecutableby_form/new.h>

#include "../expression.h"

#include "isexecutableby_form.h"

struct expression* specialize_primary_isexecutableby_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	struct expression* path = specialize_expression(tcache, scope, raw_arguments[0]);
	
	struct expression* user = specialize_expression(tcache, scope, raw_arguments[1]);
	
	struct type* path_type = type_cache_get_string_type(tcache);
	
	if (path->type != path_type || user->type != path_type)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = type_cache_get_bool_type(tcache);
	
	retval = new_isexecutableby_form_expression(type, path, user);
	
	free_expression(path);
	
	free_expression(user);
	
	EXIT;
	return retval;
}

