
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <type/list/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* sum_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct sum_form_expression* this = (void*) super;
	
	struct value* list = expression_evaluate(tcache, this->list, environment);
	
	struct value* value;
	
	switch (((struct list_type*) list->type)->element_type->kind)
	{
		case tk_int:
			value = sum_form_run_on_ints(super->type, (struct list_value*) list);
			break;
		
		case tk_float:
			value = sum_form_run_on_floats(super->type, (struct list_value*) list);
			break;
		
		default:
			TODO;
			break;
	}
	
	free_value(list);
	
	EXIT;
	return value;
}













