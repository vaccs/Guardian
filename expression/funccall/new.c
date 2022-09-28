
#include <debug.h>

#include <expression/inc.h>

#include <list/expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_funccall_expression(
	struct type* type,
	struct expression* lambda,
	struct expression_list* arguments)
{
	ENTER;
	
	struct funccall_expression* this = (void*) new_expression(
		ek_funccall,
		&funccall_expression_inheritance,
		type,
		sizeof(*this));
	
	this->lambda = inc_expression(lambda);
	
	this->arguments = inc_expression_list(arguments);
	
	EXIT;
	return (void*) this;
}

