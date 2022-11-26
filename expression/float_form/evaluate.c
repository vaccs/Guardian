
#include <assert.h>

#include <debug.h>

#include <value/struct.h>

#include <value/free.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* float_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct float_form_expression* this = (void*) super;
	
	struct value* object = expression_evaluate(tcache, this->object, environment);
	
	struct value* value;
	
	switch (object->kind)
	{
		case vk_int:
			value = float_form_run_on_int(super->type, (struct int_value*) object);
			break;
		
		case vk_string:
			value = float_form_run_on_string(super->type, (struct string_value*) object);
			break;
		
		default:
			TODO;
			break;
	}
	
	free_value(object);
	
	EXIT;
	return value;
}













