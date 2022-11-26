
#include <assert.h>

#include <stdbool.h>
#include <stdlib.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <type_cache/get_int_type.h>

#include <type_cache/get_list_type.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>

#include <value/free.h>

#include <expression/range_form/run.h>
#include <expression/range_form/new.h>

#include <expression/free.h>

#include "../expression.h"

#include "range_form.h"

struct expression* specialize_primary_range_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	struct expression* start = NULL;
	
	struct expression* end = NULL;
	
	switch (raw_len)
	{
		case 1:
			end = specialize_expression(tcache, scope, raw_arguments[0]);
			break;
		
		case 2:
			start = specialize_expression(tcache, scope, raw_arguments[0]);
			end = specialize_expression(tcache, scope, raw_arguments[1]);
			break;
		
		default:
			TODO;
			exit(1);
	}
	
	if (false
		|| (start && start->type->kind != tk_int)
		|| (  end &&   end->type->kind != tk_int))
	{
		TODO;
		exit(1);
	}
	
	struct type* etype = type_cache_get_int_type(tcache);
	struct type* ltype = type_cache_get_list_type(tcache, etype);
	
	if (true
		&& (!start || start->kind == ek_literal)
		&& (!  end ||   end->kind == ek_literal))
	{
		struct literal_expression* startlit = (void*) start;
		struct literal_expression* endlit = (void*) end;
		
		struct value* value = range_form_run(
			(struct list_type*) ltype,
			(struct int_value*) startlit->value,
			(struct int_value*) endlit->value);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else
	{
		retval = new_range_form_expression(ltype, start, end);
	}
	
	free_expression(start);
	free_expression(end);
	
	EXIT;
	return retval;
}















