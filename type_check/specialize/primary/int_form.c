
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include <type_cache/get_int_type.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <expression/inc.h>

#include <expression/int_form/new.h>

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
				TODO;
				#if 0
				retval = new_float_form_expression(type, object);
				#endif
			}
			break;
		}
		
		case tk_string:
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

