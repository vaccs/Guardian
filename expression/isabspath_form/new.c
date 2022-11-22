
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_isabspath_form_expression(
	struct type* type,
	struct expression* path)
{
	ENTER;
	
	struct isabspath_form_expression* this = (void*) new_expression(
		ek_isabspath_form,
		&isabspath_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->path = inc_expression(path);
	
	EXIT;
	return (void*) this;
}

