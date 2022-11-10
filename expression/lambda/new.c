
#include <debug.h>

#include <list/parameter/inc.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_lambda_expression(
	struct type* type,
	struct parameter_list* parameters,
	struct type* environment,
	struct expression* body)
{
	ENTER;
	
	struct lambda_expression* this = (void*) new_expression(
		ek_lambda,
		&lambda_expression_inheritance,
		type,
		sizeof(*this));
	
	this->parameters = inc_parameter_list(parameters);
	
	this->environment = environment;
	
	this->body = inc_expression(body);
	
	EXIT;
	return (void*) this;
}

