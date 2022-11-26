
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <parse/parse.h>

#include <list/expression/new.h>

#include <expression/struct.h>

#include <list/expression/append.h>

#include <expression/free.h>

#include <type_cache/get_list_type.h>

#include <list/value/new.h>

#include <list/expression/struct.h>

#include <list/value/append.h>

#include <expression/literal/struct.h>

#include <value/list/new.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <list/value/free.h>

#include <expression/list_init/new.h>

#include <list/expression/free.h>

#include "../expression.h"

#include "list_init.h"

struct expression* specialize_primary_list_init_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->elements.n);
	
	struct type* element_type = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct expression* element = specialize_expression(
			tcache, scope, expression->elements.data[i]);
		
		if (!element_type)
		{
			element_type = element->type;
		}
		else if (element_type != element->type)
		{
			TODO;
		}
		
		if (element->kind != ek_literal)
			all_literals = false;
		
		expression_list_append(elements, element);
		
		free_expression(element);
	}
	
	assert(element_type);
	
	struct type* type = type_cache_get_list_type(tcache, element_type);
	
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
		
		struct value* new = new_list_value(type, values);
		
		retval = new_literal_expression(new);
		
		free_value(new);
		
		free_value_list(values);
	}
	else
	{
		retval = new_list_init_expression(type, elements);
	}
	
	free_expression_list(elements);
	
	EXIT;
	return retval;
}

