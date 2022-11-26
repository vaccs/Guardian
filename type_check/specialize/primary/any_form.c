
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <type/list/struct.h>

#include <type/struct.h>

#include <expression/struct.h>

#include <type_cache/get_bool_type.h>

#include <expression/literal/struct.h>

#include <expression/literal/new.h>

#include <expression/free.h>

#include <value/free.h>

#include <expression/any_form/new.h>
#include <expression/any_form/run.h>

#include "../expression.h"

#include "any_form.h"

struct expression* specialize_primary_any_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* list = specialize_expression(tcache, scope, raw_argument);
	
	if (list->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct list_type* ltype = (void*) list->type;
	
	if (ltype->element_type->kind != tk_bool)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = type_cache_get_bool_type(tcache);
	
	if (list->kind == ek_literal)
	{
		struct literal_expression* listlit = (void*) list;
		
		struct list_value* lvalue = (void*) listlit->value;
		
		struct value* value = any_form_run(type, lvalue);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else
	{
		retval = new_any_form_expression(type, list);
	}
	
	free_expression(list);
	
	EXIT;
	return retval;
}

