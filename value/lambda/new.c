
#include <debug.h>

#include <expression/inc.h>

#include <list/parameter/inc.h>

#include <scope/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_lambda_value(
	struct type* type,
	unsigned id,
	struct parameter_list* parameters,
	struct scope* captured,
	struct expression* body)
{
	ENTER;
	
	struct lambda_value* this = (void*) new_value(
		type,
		vk_lambda,
		&lambda_value_inheritance,
		sizeof(*this));
	
	this->id = id;
	
	this->parameters = inc_parameter_list(parameters);
	
	this->captured = inc_scope(captured);
	
	this->body = inc_expression(body);
	
	EXIT;
	return (void*) this;
}

