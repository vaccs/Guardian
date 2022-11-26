
#include <assert.h>
#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <list/expression/struct.h>

/*#include <value/lambda/call.h>*/
/*#include <value/free.h>*/

#include "../evaluate.h"

#include "struct.h"
#include "run.h"
#include "evaluate.h"

struct value* funccall_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct funccall_expression* this = (void*) super;
	
	struct value* lambda = expression_evaluate(tcache, this->lambda, environment);
	
	assert(lambda->kind == vk_lambda);
	
	struct value_list* arguments = new_value_list();
	
	for (unsigned i = 0, n = this->arguments->n; i < n; i++)
	{
		struct value* argument = expression_evaluate(tcache, this->arguments->data[i], environment);
		
		value_list_append(arguments, argument);
		
		free_value(argument);
	}
	
	struct value* result = funccall_run(tcache, (void*) lambda, arguments);
	
	free_value(lambda);
	
	free_value_list(arguments);
	
	EXIT;
	return result;
}













