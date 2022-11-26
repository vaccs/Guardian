
#include <assert.h>

#include <debug.h>

#include <value/lambda/new.h>

#include "struct.h"
#include "evaluate.h"

struct value* lambda_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	assert(super->kind == ek_lambda);
	
	struct lambda_expression* this = (void*) super;
	
	struct value* lambda = new_lambda_value(
		/* type: */ super->type,
		/* parameters: */ this->parameters,
		/* captured: */ environment,
		/* body: */ this->body);
	
	EXIT;
	return lambda;
}
