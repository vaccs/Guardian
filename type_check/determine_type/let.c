
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include <defines/argv0.h>

#include <parse/parse.h>

#include <string/new.h>
#include <string/free.h>

#include <stringtree/stream.h>
#include <stringtree/free.h>

#include <type/print.h>

#include <type_check/scope/push.h>
#include <type_check/scope/pop.h>
#include <type_check/scope/declare.h>

#include "lambda.h"
#include "expression.h"
#include "let.h"

struct type* determine_type_of_let_expression(
	struct zebu_let_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* retval;
	ENTER;
	
	if (expression->base)
	{
		retval = determine_type_of_lambda_expression(expression->base, tcache, scope);
	}
	else if (expression->let)
	{
		type_check_scope_push(scope);
		
		TODO;
		#if 0
		for (unsigned i = 0, n = expression->parameters.n; i < n; i++)
		{
			struct string* name = new_string_from_token(expression->parameters.data[i]->name);
			
			type_check_scope_declare(scope, name);
			
			free_string(name);
		}
		
		#ifdef VERBOSE
		printf("let: ");
		#endif
		
		for (unsigned i = 0, n = expression->parameters.n; i < n; i++)
		{
			struct string* name = new_string_from_token(expression->parameters.data[i]->name);
			
			#ifdef VERBOSE
			if (i) printf(", ");
			
			printf("'%.*s' = ", name->len, name->chars);
			#endif
			
			struct type* type = determine_type_of_expression(
				expression->parameters.data[i]->expression,
				tcache, scope);
			
			#ifdef VERBOSE
			{
				struct stringtree* tree = type_print2(type);
				stringtree_stream(tree, stdout);
				free_stringtree(tree);
			}
			#endif
			
			type_check_scope_declare_type(scope, name, type);
			
			free_string(name);
		}
		
		printf(": ");
		
		retval = determine_type_of_let_expression(
			expression->body, tcache, scope);
		#endif
		
		type_check_scope_pop(scope);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}





















