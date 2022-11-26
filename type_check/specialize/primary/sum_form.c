
#include <assert.h>

#include <stdlib.h>

#include <stdbool.h>

#include <debug.h>

#include <value/free.h>

#include <expression/struct.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <expression/sum_form/run.h>
#include <expression/sum_form/new.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
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
	
	struct expression* list_exp = specialize_expression(tcache, scope, raw_argument);
	
	bool all_literals = list_exp->kind == ek_literal;
	
	if (list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = ((struct list_type*) list_exp->type)->element_type;
	
	switch (type->kind)
	{
		case tk_int:
		{
			if (all_literals)
			{
				struct literal_expression* lit = (void*) list_exp;
				
				struct value* value = sum_form_run_on_ints(type, (struct list_value*) lit->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_sum_form_expression(type, list_exp);
			}
			break;
		}
		
		case tk_float:
		{
			if (all_literals)
			{
				struct literal_expression* lit = (void*) list_exp;
				
				struct value* value = sum_form_run_on_floats(type, (struct list_value*) lit->value);
				
				retval = new_literal_expression(value);
				
				free_value(value);
			}
			else
			{
				retval = new_sum_form_expression(type, list_exp);
			}
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	free_expression(list_exp);
	
	EXIT;
	return retval;
}













