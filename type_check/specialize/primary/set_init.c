
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <parse/parse.h>

#include "../expression.h"

#include <expression/struct.h>

#include <list/expression/new.h>

#include <list/expression/foreach.h>

#include <list/expression/append.h>

#include <expression/free.h>

#include <type_cache/get_set_type.h>

#include <list/value/new.h>

#include <list/expression/struct.h>

#include <list/value/append.h>

#include <expression/literal/struct.h>

#include <value/free.h>

#include <list/value/free.h>

#include <expression/literal/new.h>

#include <expression/set_init/run.h>

#include <list/expression/free.h>

#include <expression/set_init/new.h>

#include "set_init.h"

struct expression* specialize_primary_set_init_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->elements.n);
	
	struct type* eletype = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct expression* eleexp = specialize_expression(
			tcache, scope, expression->elements.data[i]);
		
		if (!eletype)
		{
			eletype = eleexp->type;
		}
		else if (eletype != eleexp->type)
		{
			TODO;
		}
		
		if (eleexp->kind != ek_literal)
			all_literals = false;
		
		expression_list_append(elements, eleexp);
		
		free_expression(eleexp);
	}
	
	assert(eletype);
	
	struct type* type = type_cache_get_set_type(tcache, eletype);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_list* values = new_value_list();
		
		for (unsigned i = 0, n = expression->elements.n; i < n; i++)
		{
			struct expression* element = elements->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(values, le->value);
		}
		
		struct value* value = set_init_run(type, values);
		
		retval = new_literal_expression(value);
		
		free_value(value);
		
		free_value_list(values);
	}
	else
	{
		retval = new_set_init_expression(type, elements);
	}
	
	free_expression_list(elements);
	
	EXIT;
	return retval;
}

