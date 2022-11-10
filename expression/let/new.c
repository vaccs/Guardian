
#include <debug.h>

#include <list/named_expression/inc.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_let_expression(
	struct type* type,
	struct type* environment,
	struct named_expression_list* parameters,
	struct expression* body)
{
	ENTER;
	
	struct let_expression* this = (void*) new_expression(
		ek_let,
		&let_expression_inheritance,
		type,
		sizeof(*this));
	
	this->environment = environment;
	
	this->parameters = inc_named_expression_list(parameters);
	
	this->body = inc_expression(body);
	
	EXIT;
	return (void*) this;
}

