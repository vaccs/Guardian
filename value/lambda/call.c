
#include <debug.h>

#include <scope/new.h>
#include <scope/declare.h>
#include <scope/free.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>
#include <list/value/struct.h>

#include <expression/evaluate.h>

#include "struct.h"
#include "call.h"

struct value* lambda_value_call(
	struct lambda_value* this,
	struct value_list* arguments)
{
	ENTER;
	
	struct scope* scope = new_scope();
	
	assert(this->parameters->n == arguments->n);
	
	for (unsigned i = 0, n = arguments->n; i < n; i++)
	{
		struct parameter* parameter = this->parameters->data[i];
		struct value* value = arguments->data[i];
		
		assert(parameter->type == value->type);
		
		scope_declare(scope, parameter->name, value);
	}
	
	// push all captured values into scope
	for (unsigned i = 0, n = this->captured->n; i < n; i++)
	{
		TODO;
	}
	
	// evaluate inner expression
	struct value* retval = expression_evaluate(this->body, scope);
	
	free_scope(scope);
	
	EXIT;
	return retval;
}















