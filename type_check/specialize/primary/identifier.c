
#include <stdlib.h>
#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <defines/argv0.h>

#include <type_check/scope/lookup.h>

#include <expression/literal/new.h>
#include <expression/variable/new.h>

#include <value/free.h>

#include "identifier.h"

struct expression* specialize_primary_identifier_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	struct string* name = new_string_from_token(zexpression->identifier);
	
	struct type* type = NULL;
	struct value* value = NULL;
	
	if (!type_check_scope_lookup(scope, name, &type, &value))
	{
		fprintf(stderr, "%s: use of undefined variable '%s'!\n",
			argv0, (char*) zexpression->identifier->data);
		exit(1);
	}
	else if (value)
	{
		retval = new_literal_expression(value);
	}
	else
	{
		retval = new_variable_expression(type, name);
	}
	
	free_string(name);
	
	free_value(value);
	
	EXIT;
	return retval;
}

