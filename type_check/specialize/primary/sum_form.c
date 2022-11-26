
#include <assert.h>

#include <stdlib.h>

#include <stdbool.h>

#include <debug.h>

#include <expression/struct.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <expression/sum_form/new.h>
#include <expression/free.h>

#include "../expression.h"

#include "sum_form.h"

struct expression* specialize_primary_sum_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	bool all_literals = true;
	
	struct expression* list_exp = specialize_expression(tcache, scope, raw_argument);
	
	if (list_exp->kind != ek_literal)
		all_literals = false;
	
	if (list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = ((struct list_type*) list_exp->type)->element_type;
	
	if (type->kind != tk_int && type->kind != tk_float)
	{
		TODO;
	}
	else if (all_literals)
	{
		TODO;
	}
	else
	{
		retval = new_sum_form_expression(type, list_exp);
	}
	
	free_expression(list_exp);
	
	EXIT;
	return retval;
}

