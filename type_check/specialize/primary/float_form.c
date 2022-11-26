
#include <assert.h>

#include <stdlib.h>

#include <expression/free.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <expression/inc.h>

#include <type_cache/get_float_type.h>

#include <expression/literal/new.h>
#include <expression/literal/struct.h>

#include <value/free.h>

#include <expression/float_form/run.h>
#include <expression/float_form/new.h>

#include "../expression.h"

#include "float_form.h"

struct expression* specialize_primary_float_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	struct type* type = type_cache_get_float_type(tcache);
	
	switch (object->type->kind)
	{
		case tk_float:
			retval = inc_expression(object);
			break;
		
		case tk_int:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* lit = (void*) object;
				
				struct value* value = float_form_run_on_int(type, (struct int_value*) lit->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_float_form_expression(type, object);
			}
			break;
		}
		
		case tk_string:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* lit = (void*) object;
				
				struct value* value = float_form_run_on_string(type, (struct string_value*) lit->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_float_form_expression(type, object);
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

