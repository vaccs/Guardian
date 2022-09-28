
#include <debug.h>

#include <parse/parse.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <type/free.h>

#include <value/lambda/new.h>
#include <value/free.h>

#include <parameter/new.h>
#include <parameter/free.h>

#include <list/parameter/new.h>
#include <list/parameter/is_nonempty.h>
#include <list/parameter/append.h>
#include <list/parameter/free.h>

#include <expression/lambda/new.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include "../unresolved/foreach.h"

#include "../build_type.h"

#include "conditional.h"
#include "lambda.h"

struct expression* specialize_lambda_expression(
	struct type_cache* tcache,
	struct zebu_lambda_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_conditional_expression(tcache, zexpression->base);
	}
	else if (zexpression->lambda)
	{
		struct parameter_list* parameters = new_parameter_list();
		
		if (zexpression->name)
		{
			struct type* type = build_type(tcache, zexpression->type);
			
			struct string* name = new_string_from_token(zexpression->name);
			
			struct parameter* parameter = new_parameter(name, type);
			
			parameter_list_append(parameters, parameter);
			
			free_parameter(parameter);
			
			free_string(name);
			
			for (unsigned i = 0, n = zexpression->parameters.n; i < n; i++)
			{
				struct zebu_0$parameter* raw_parameter = zexpression->parameters.data[i];
				
				if (raw_parameter->type)
				{
					struct type* new = build_type(tcache, raw_parameter->type);
					
					free_type(type), type = new;
				}
				
				struct string* name = new_string_from_token(raw_parameter->name);
				
				struct parameter* parameter = new_parameter(name, type);
				
				parameter_list_append(parameters, parameter);
				
				free_parameter(parameter);
				
				free_string(name);
			}
			
			free_type(type);
		}
		
		struct parameter_list* captured = new_parameter_list();
		
		unresolved_foreach2(zexpression->lambda_captures, ({
			void runme(struct string* name, struct type* type, struct value* value)
			{
				if (!value)
				{
					struct parameter* parameter = new_parameter(name, type);
					
					parameter_list_append(captured, parameter);
					
					free_parameter(parameter);
				}
			}
			runme;
		}));
		
		struct expression* body = specialize_lambda_expression(tcache, zexpression->lambda);
		
		if (parameter_list_is_nonempty(captured))
		{
			retval = new_lambda_expression(parameters, captured, body);
		}
		else
		{
			// if we know all the values for the capture, this should be
			// a literal_expression instead
			struct value* new = new_lambda_value(tcache, parameters, captured, body);
			
			retval = new_literal_expression(new);
			
			free_value(new);
		}
		
		free_parameter_list(parameters);
		free_parameter_list(captured);
		free_expression(body);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













