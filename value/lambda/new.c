
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include <type_cache/get_type/lambda.h>

#include <type/free.h>

#include <list/parameter/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_lambda_value(
	struct type_cache* tcache,
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body)
{
	ENTER;
	
	struct type* type = type_cache_get_lambda_type(tcache, parameters, body->type);
	
	struct lambda_value* this = (void*) new_value(
		type,
		vk_lambda,
		&lambda_value_inheritance,
		sizeof(*this));
	
	this->parameters = inc_parameter_list(parameters);
	
	this->captured = inc_parameter_list(captured);
	
	this->body = inc_expression(body);
	
	free_type(type);
	
	EXIT;
	return (void*) this;
}

