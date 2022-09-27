
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "new.h"

struct expression* new_lambda_expression(
	struct parameter_list* parameters,
	struct parameter_list* captured,
	struct expression* body)
{
	ENTER;
	
	TODO;
	#if 0
	struct lambda_expression* this = (void*) new_expression(
		ek_lambda,
		body->type,
		sizeof(*this));
	
	this->parameters = parameters;
	this->captured = captured;
	this->body = inc_expression(body);
	
	EXIT;
	return (void*) this;
	#endif
}

