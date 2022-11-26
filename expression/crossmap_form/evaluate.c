
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <list/expression/foreach.h>

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* crossmap_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct crossmap_form_expression* this = (void*) super;
	
	struct value* lambda = expression_evaluate(tcache, this->lambda, environment);
	
	assert(lambda->kind == vk_lambda);
	
	struct value_list* arguments = new_value_list();
	
	expression_list_foreach(this->arguments, ({
		void runme(struct expression* expression)
		{
			struct value* value = expression_evaluate(tcache, expression, environment);
			
			value_list_append(arguments, value);
			
			free_value(value);
		}
		runme;
	}));
	
	struct value* value = crossmap_form_run(tcache, super->type,
		(struct lambda_value*) lambda, arguments);
	
	free_value(lambda);
	
	free_value_list(arguments);
	
	EXIT;
	return value;
}













