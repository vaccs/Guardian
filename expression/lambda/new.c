
#include <debug.h>

#include <list/parameter/inc.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_lambda_expression(
	struct type* type,
	unsigned id,
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body)
{
	ENTER;
	
	struct lambda_expression* this = (void*) new_expression(
		ek_lambda,
		&lambda_expression_inheritance,
		type,
		sizeof(*this));
	
	this->parameters = inc_parameter_list(parameters);
	this->captured = inc_parameter_list(captured);
	this->body = inc_expression(body);
	
	this->id = id;
	
	EXIT;
	return (void*) this;
}

