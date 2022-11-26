
#include <debug.h>

#include <list/named_type/inc.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_lambda_expression(
	struct type* type,
	struct named_type_list* parameters,
	struct expression* body)
{
	ENTER;
	
	struct lambda_expression* this = (void*) new_expression(
		ek_lambda,
		&lambda_expression_inheritance,
		type,
		sizeof(*this));
	
	this->parameters = inc_named_type_list(parameters);
	
	this->body = inc_expression(body);
	
	EXIT;
	return (void*) this;
}

