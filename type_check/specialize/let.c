
#include <assert.h>
#include <stdbool.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <named/expression/new.h>
#include <named/expression/free.h>

#include <list/named_expression/new.h>
#include <list/named_expression/append.h>
#include <list/named_expression/free.h>

#include <type_check/scope/struct.h>
#include <type_check/scope/layer.h>
#include <type_check/scope/push.h>
#include <type_check/scope/pop.h>
#include <type_check/scope/declare.h>

#include <type_cache/get_type/environment.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/let/new.h>
#include <expression/inc.h>
#include <expression/free.h>

#include "shared.h"
#include "expression.h"
#include "lambda.h"
#include "let.h"

struct expression* specialize_let_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_let_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_lambda_expression(tcache, sshared, scope, zexpression->base);
	}
	else if (zexpression->let)
	{
		type_check_scope_push(scope);
		
		for (unsigned i = 0, n = zexpression->parameters.n; i < n; i++)
		{
			struct string* name = new_string_from_token(zexpression->parameters.data[i]->name);
			
			type_check_scope_declare(scope, name);
			
			free_string(name);
		}
		
		struct named_expression_list* parameters = new_named_expression_list();
		
		bool all_literals = true;
		
		for (unsigned i = 0, n = zexpression->parameters.n; i < n; i++)
		{
			struct string* name = new_string_from_token(zexpression->parameters.data[i]->name);
			
			struct expression* expression = specialize_expression(
				tcache, sshared, scope,
				zexpression->parameters.data[i]->expression);
			
			type_check_scope_declare_type(scope, name, expression->type);
			
			struct named_expression* nexpression = new_named_expression(name, expression);
			
			named_expression_list_append(parameters, nexpression);
			
			if (expression->kind == ek_literal)
			{
				struct literal_expression* spef = (void*) expression;
				
				type_check_scope_declare_value(scope, name, spef->value);
			}
			else
			{
				all_literals = false;
			}
			
			free_named_expression(nexpression);
			free_expression(expression);
			free_string(name);
		}
		
		// make environment type
		struct type* environment = type_cache_get_environment_type(
			tcache, sshared->environment, scope->head->tree);
		
		struct type* old = sshared->environment;
		sshared->environment = environment;
		struct expression* body = specialize_let_expression(tcache, sshared, scope, zexpression->body);
		sshared->environment = old;
		
		if (all_literals)
			retval = inc_expression(body);
		else
			retval = new_let_expression(body->type, environment, parameters, body);
		
		free_named_expression_list(parameters);
		type_check_scope_pop(scope);
		free_expression(body);
	}
	else
	{
		TODO;
	}
	
	
	EXIT;
	return retval;
}











