
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include <type_cache/get_int_type.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <expression/inc.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>

#include <value/free.h>

#include <expression/int_form/new.h>
#include <expression/int_form/run.h>

#include "../expression.h"

#include "int_form.h"

struct expression* specialize_primary_int_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	switch (object->type->kind)
	{
		case tk_int:
			retval = inc_expression(object);
			break;
		
		case tk_float:
		{
			if (object->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				retval = new_int_form_expression(type, object);
			}
			break;
		}
		
		case tk_string:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* lit = (void*) object;
				
				struct value* value = int_form_run_on_string(
					type, (struct string_value*) lit->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_int_form_expression(type, object);
			}
			break;
		}
		
		case tk_lambda:
		{
			// "cannot cast lambda to float!"
			TODO;
			exit(1);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	free_expression(object);
	
	EXIT;
	return retval;
}







