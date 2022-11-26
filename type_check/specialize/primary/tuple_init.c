
#include <stdbool.h>

#include <debug.h>

#include <list/type/new.h>

#include <list/expression/new.h>

#include <parse/parse.h>

#include "../expression.h"

#include <expression/struct.h>

#include <list/type/append.h>

#include <list/expression/append.h>

#include <expression/free.h>

#include <expression/tuple_init/new.h>

#include <type_cache/get_tuple_type.h>

#include <list/value/new.h>

#include <list/expression/struct.h>

#include <list/value/append.h>

#include <expression/literal/struct.h>

#include <value/tuple/new.h>

#include <expression/literal/new.h>

#include <list/value/free.h>

#include <value/free.h>

#include <list/expression/free.h>

#include <list/type/free.h>

#include "tuple_init.h"

struct expression* specialize_tuple_init_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	struct type_list* subtypes = new_type_list();
	
	bool all_literals = true;
	
	struct expression_list* subexpressions = new_expression_list();
	
	unsigned i, n;
	
	for (i = 0, n = zexpression->elements.n; i < n; i++)
	{
		struct expression* subexpression = specialize_expression(
			tcache, scope, zexpression->elements.data[i]);
		
		if (subexpression->kind != ek_literal)
			all_literals = false;
		
		type_list_append(subtypes, subexpression->type);
		
		expression_list_append(subexpressions, subexpression);
		
		free_expression(subexpression);
	}
	
	struct type* type = type_cache_get_tuple_type(tcache, subtypes);
	
	if (all_literals)
	{
		struct value_list* subvalues = new_value_list();
		
		for (i = 0; i < n; i++)
		{
			struct expression* expression = subexpressions->data[i];
			
			struct literal_expression* spef = (void*) expression;
			
			value_list_append(subvalues, spef->value);
		}
		
		struct value* value = new_tuple_value(type, subvalues);
		
		retval = new_literal_expression(value);
		
		free_value_list(subvalues);
		free_value(value);
	}
	else
	{
		retval = new_tuple_init_expression(type, subexpressions);
	}
	
	free_expression_list(subexpressions);
	
	free_type_list(subtypes);
	
	EXIT;
	return retval;
}

