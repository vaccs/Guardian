
#include <assert.h>

#include <stdbool.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <stdlib.h>

#include <type/lambda/struct.h>

#include <list/type/struct.h>

#include <list/expression/new.h>

#include <type/list/struct.h>

#include <list/expression/append.h>

#include <expression/free.h>

#include <type_cache/get_list_type.h>

#include <expression/literal/struct.h>

#include <list/value/new.h>

#include <list/expression/struct.h>

#include <list/value/append.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <list/value/free.h>

#include <list/expression/free.h>

#include <expression/crossmap_form/new.h>
#include <expression/crossmap_form/run.h>

#include "../expression.h"

#include "crossmap_form.h"

struct expression* specialize_primary_crossmap_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len >= 2);
	
	bool all_literals = true;
	
	struct expression* lambda_exp = specialize_expression(tcache, scope, raw_arguments[0]);
	
	if (lambda_exp->kind != ek_literal)
		all_literals = false;
	
	if (lambda_exp->type->kind != tk_lambda)
	{
		TODO;
		exit(1);
	}
	
	struct lambda_type* lambda_type = (void*) lambda_exp->type;
	
	raw_arguments++, raw_len--;
	
	if (lambda_type->parameters->n != raw_len)
	{
		TODO;
		exit(1);
	}
	
	struct expression_list* arguments = new_expression_list();
	
	for (unsigned i = 0, n = raw_len; i < n; i++)
	{
		struct expression* arg = specialize_expression(tcache, scope, raw_arguments[i]);
		
		if (arg->kind != ek_literal)
			all_literals = false;
		
		if (arg->type->kind != tk_list)
		{
			TODO;
			exit(1);
		}
		
		struct list_type* list_type = (void*) arg->type;
		
		if (lambda_type->parameters->data[i] != list_type->element_type)
		{
			TODO;
			exit(1);
		}
		
		expression_list_append(arguments, arg);
		
		free_expression(arg);
	}
	
	struct type* type = type_cache_get_list_type(tcache, lambda_type->rettype);
	
	if (all_literals)
	{
		struct literal_expression* le = (void*) lambda_exp;
		
		struct lambda_value* lambda = (void*) le->value;
		
		struct value_list* valargs = new_value_list();
		
		for (unsigned i = 0, n = arguments->n; i < n; i++)
		{
			struct expression* element = arguments->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(valargs, le->value);
		}
		
		struct value* result = crossmap_form_run(tcache, type, lambda, valargs);
		
		retval = new_literal_expression(result);
		
		free_value(result);
		
		free_value_list(valargs);
	}
	else
	{
		retval = new_crossmap_form_expression(type, lambda_exp, arguments);
	}
	
	free_expression_list(arguments);
	
	free_expression(lambda_exp);
	
	EXIT;
	return retval;
}

