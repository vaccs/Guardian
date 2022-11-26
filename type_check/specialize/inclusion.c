
#include <type/list/struct.h>

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

/*#include <expression/has/new.h>*/
/*#include <expression/free.h>*/

#include <parse/parse.h>

#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/string_contains/new.h>
#include <expression/string_contains/run.h>
#include <expression/list_contains/new.h>
#include <expression/list_contains/run.h>
#include <expression/dict_contains/new.h>
#include <expression/dict_contains/run.h>
#include <expression/set_contains/new.h>
#include <expression/set_contains/run.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include <type/dict/struct.h>
/*#include <type/list/struct.h>*/
#include <type/set/struct.h>
#include <type/struct.h>

#include <type_cache/get_bool_type.h>

#include "logical_or.h"
#include "inclusion.h"

struct expression* specialize_inclusion_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_inclusion_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->container)
	{
		struct expression* element = specialize_logical_or_expression(tcache, scope, zexpression->base);
		struct expression* container = specialize_logical_or_expression(tcache, scope, zexpression->container);
		
		bool all_literals = (element->kind == ek_literal && container->kind == ek_literal);
		
		struct type* type = type_cache_get_bool_type(tcache);
		
		switch (container->type->kind)
		{
			case tk_string:
			{
				if (element->type != container->type)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					struct literal_expression* elelit = (void*) element;
					struct literal_expression* conlit = (void*) container;
					
					struct value* value = string_contains_run(
						type, (struct string_value*) elelit->value, (struct string_value*) conlit->value);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_string_contains_expression(type, element, container);
				}
				
				break;
			}
			
			case tk_list:
			{
				struct list_type* ltype = (void*) container->type;
				
				if (element->type != ltype->element_type)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					struct literal_expression* elelit = (void*) element;
					struct literal_expression* conlit = (void*) container;
					
					struct value* value = list_contains_run(
						type, elelit->value, (struct list_value*) conlit->value);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_list_contains_expression(type, element, container);
				}
				break;
			}
			
			case tk_dict:
			{
				struct dict_type* dtype = (void*) container->type;
				
				if (element->type != dtype->key)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					struct literal_expression* elelit = (void*) element;
					struct literal_expression* conlit = (void*) container;
					
					struct value* value = dict_contains_run(
						type, elelit->value, (struct dict_value*) conlit->value);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_dict_contains_expression(type, element, container);
				}
				break;
			}
			
			case tk_set:
			{
				struct set_type* stype = (void*) container->type;
				
				if (element->type != stype->element_type)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					struct literal_expression* elelit = (void*) element;
					struct literal_expression* conlit = (void*) container;
					
					struct value* value = set_contains_run(
						type, elelit->value, (struct set_value*) conlit->value);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					retval = new_set_contains_expression(type, element, container);
				}
				break;
			}
			
			default:
				TODO;
				break;
		}
		
		free_expression(element);
		free_expression(container);
	}
	else if (zexpression->base)
	{
		retval = specialize_logical_or_expression(tcache, scope, zexpression->base);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

