
#include <debug.h>

#include <list/parameter/inc.h>

#include <type/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_lambda_type(
	unsigned id,
	struct parameter_list* parameters,
	struct type* rettype)
{
	ENTER;
	
	struct lambda_type* this = (void*) new_type(
		id,
		tk_lambda,
		&lambda_type_inheritance,
		sizeof(*this));
	
	this->parameters = inc_parameter_list(parameters);
	
	this->rettype = inc_type(rettype);
	
	EXIT;
	return (void*) this;
}

