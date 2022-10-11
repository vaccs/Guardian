
#include <debug.h>

#include <list/type/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_lambda_type(
	unsigned id,
	struct type_list* parameters,
	struct type* rettype)
{
	ENTER;
	
	struct lambda_type* this = (void*) new_type(
		id,
		tk_lambda,
		&lambda_type_inheritance,
		sizeof(*this));
	
	this->parameters = inc_type_list(parameters);
	
	this->rettype = rettype;
	
	EXIT;
	return (void*) this;
}

