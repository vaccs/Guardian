
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <string/new.h>
#include <string/free.h>

#include <named/type/new.h>
#include <named/type/compare.h>
#include <named/type/free.h>

#include <type/free.h>

#include <value/lambda/new.h>
#include <value/free.h>

#include <parameter/new.h>
#include <parameter/free.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <type/print.h>

#include <list/parameter/new.h>
#include <list/parameter/is_nonempty.h>
#include <list/parameter/append.h>
#include <list/parameter/free.h>

#include <capture/new.h>
#include <capture/free.h>

#include <list/capture/new.h>
#include <list/capture/append.h>
#include <list/capture/is_nonempty.h>
#include <list/capture/free.h>

#include <type_cache/get_type/lambda.h>

#include <expression/struct.h>	
#include <expression/lambda/new.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include "../unresolved/foreach.h"
#include "../unresolved/is_nonempty.h"

#include "../build_type.h"

#include "shared.h"
#include "conditional.h"
#include "lambda.h"

struct expression* specialize_lambda_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct zebu_lambda_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_conditional_expression(tcache, sshared, zexpression->base);
	}
	else if (zexpression->lambda)
	{
		struct type_list* parameter_types = new_type_list();
		
		struct parameter_list* parameters = new_parameter_list();
		
		if (zexpression->name)
		{
			struct type* type = build_type(tcache, zexpression->type);
			
			struct string* name = new_string_from_token(zexpression->name);
			
			struct parameter* parameter = new_parameter(name, type);
			
			parameter_list_append(parameters, parameter);
			
			type_list_append(parameter_types, type);
			
			free_parameter(parameter);
			
			free_string(name);
			
			for (unsigned i = 0, n = zexpression->parameters.n; i < n; i++)
			{
				struct zebu_0$parameter* raw_parameter = zexpression->parameters.data[i];
				
				if (raw_parameter->type)
				{
					struct type* new = build_type(tcache, raw_parameter->type);
					
					type = new;
				}
				
				struct string* name = new_string_from_token(raw_parameter->name);
				
				struct parameter* parameter = new_parameter(name, type);
				
				type_list_append(parameter_types, type);
				
				parameter_list_append(parameters, parameter);
				
				free_parameter(parameter);
				
				free_string(name);
			}
		}
		
		struct type* rettype = build_type(tcache, zexpression->rettype);
		
		struct type* type = type_cache_get_lambda_type(tcache, parameter_types, rettype);
		
		struct expression* body = specialize_lambda_expression(tcache, sshared, zexpression->lambda);
		
		if (rettype != body->type)
		{
			TODO;
			exit(1);
		}
		
		struct capture_list* captures = new_capture_list();
		
		unresolved_foreach5(zexpression->lambda_captures, ({
			void runme(
				struct string* name,
				enum variable_expression_kind kind,
				struct type* type,
				struct value* value)
			{
				if (!value)
				{
					switch (kind)
					{
						case vek_parameter:
						case vek_captured:
						{
							struct capture* capture = new_capture(name, kind, type);
							
							capture_list_append(captures, capture);
							
							free_capture(capture);
							break;
						}
						
						case vek_declare:
						case vek_grammar_rule:
							break;
						
						default:
							TODO;
							break;
					}
				}
			}
			runme;
		}));
		
		// if (capture_list_is_nonempty(captures))
		{
			retval = new_lambda_expression(type, sshared->lambda_id++, parameters, captures, body);
		}
		#if 0
		else
		{
			struct value* new = new_lambda_value(type, parameters, NULL, body);
			
			retval = new_literal_expression(new);
			
			free_value(new);
		}
		#endif
		
		free_capture_list(captures);
		
		free_type_list(parameter_types);
		
		free_parameter_list(parameters);
		
		free_expression(body);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}













