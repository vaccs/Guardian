
#include <debug.h>

#include <parse/parser.h>

#include <list/expression/struct.h>
#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <expression/struct.h>
#include <expression/variable/new.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>

#include <type_cache/get_type/list.h>

#include <type/free.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <value/integer/new.h>
#include <value/list/new.h>
#include <value/free.h>

#include "expression.h"
#include "primary.h"

static struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer)
{
	ENTER;
	
	dpvs(integer->data);
	
	errno = 0;
	
	char* m;
	signed long number = strtol((void*) integer->data, &m, 0);
	
	if (errno || *m)
	{
		TODO;
		exit(1);
	}
	
	dpv(number);
	
	struct value* value = new_integer_value(tcache, number);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_identifier_expression(
	struct type_cache* tcache,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->value)
	{
		retval = new_literal_expression(zexpression->value);
	}
	else
	{
		struct string* name = new_string_from_token(zexpression->identifier);
		
		retval = new_variable_expression(zexpression->type, name);
		
		free_string(name);
	}
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_list_expression(
	struct type_cache* tcache,
	struct zebu_expression** raw_elements, unsigned len)
{
	ENTER;
	
	dpv(len);
	
	assert(len);
	
	struct type* element_type = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = len; i < n; i++)
	{
		struct expression* element = specialize_expression(tcache, raw_elements[i]);
		
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
	}
	
	struct type* type = type_cache_get_list_type(tcache, element_type);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_list* values = new_value_list();
		
		for (unsigned i = 0, n = len; i < n; i++)
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
		TODO;
	}
	
	free_type(type);
	
	free_expression_list(elements);
	
	EXIT;
	return retval;
}

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->integer_literal)
	{
		retval = specialize_primary_integer_expression(tcache, zexpression->integer_literal);
	}
	else if (zexpression->float_literal)
	{
		TODO;
	}
	else if (zexpression->character_literal)
	{
		TODO;
	}
	else if (zexpression->string_literal)
	{
		TODO;
	}
	else if (zexpression->identifier)
	{
		retval = specialize_primary_identifier_expression(tcache, zexpression);
	}
	else if (zexpression->tuple)
	{
		TODO;
	}
	else if (zexpression->list)
	{
		retval = specialize_primary_list_expression(tcache,
			zexpression->elements.data, zexpression->elements.n);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















