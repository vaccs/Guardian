
#include <assert.h>

#include <stdlib.h>
#include <stdbool.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>

#include <type/lambda/struct.h>

#include <type/list/struct.h>

#include <list/type/struct.h>

#include <value/free.h>

#include <expression/literal/new.h>
#include <expression/literal/struct.h>

#include <expression/filter_form/run.h>
#include <expression/filter_form/new.h>

#include <expression/free.h>

#include "../expression.h"

#include "map_form.h"

struct expression* specialize_primary_filter_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len == 2);
	
	struct expression* lambda_exp = specialize_expression(tcache, scope, raw_arguments[0]);
	
	struct expression* list_exp = specialize_expression(tcache, scope, raw_arguments[1]);
	
	bool all_literals = lambda_exp->kind == ek_literal && list_exp->kind == ek_literal;
	
	if (lambda_exp->type->kind != tk_lambda || list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct lambda_type* ftype = (void*) lambda_exp->type;
	
	struct list_type* ltype = (void*) list_exp->type;
	
	if (false
		|| ftype->rettype->kind != tk_bool
		|| ftype->parameters->n != 1
		|| ftype->parameters->data[0] != ltype->element_type)
	{
		TODO;
		exit(1);
	}
	
	if (all_literals)
	{
		struct literal_expression* fe = (void*) lambda_exp;
		
		struct lambda_value* lambda = (void*) fe->value;
		
		struct literal_expression* le = (void*) list_exp;
		
		struct list_value* list = (void*) le->value;
		
		struct value* result = filter_form_run(tcache, list_exp->type, lambda, list);
		
		retval = new_literal_expression(result);
		
		free_value(result);
	}
	else
	{
		retval = new_filter_form_expression(list_exp->type, lambda_exp, list_exp);
	}
	
	free_expression(lambda_exp);
	
	free_expression(list_exp);
	
	EXIT;
	return retval;
}








