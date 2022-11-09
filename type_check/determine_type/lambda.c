
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <type_cache/get_type/lambda.h>

#include "../build_type.h"

#include "conditional.h"
#include "lambda.h"

struct type* determine_type_of_lambda_expression(
	struct zebu_lambda_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_conditional_expression(expression->base, tcache, scope);
	}
	else if (expression->lambda)
	{
		struct type_list* parameter_types = new_type_list();
		
		if (expression->type)
		{
			struct type* type = build_type(tcache, expression->type);
			
			type_list_append(parameter_types, type);
			
			for (unsigned i = 0, n = expression->parameters.n; i < n; i++)
			{
				struct zebu_0$parameter* ele = expression->parameters.data[i];
				
				if (ele->type)
				{
					TODO;
				}
				else
				{
					type_list_append(parameter_types, type);
				}
			}
		}
		
		struct type* rettype = build_type(tcache, expression->rettype);
		
		type = type_cache_get_lambda_type(tcache, parameter_types, rettype);
		
		free_type_list(parameter_types);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}














