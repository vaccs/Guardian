
#include <debug.h>

#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_any_form_expression(
	struct type* type,
	struct expression* list)
{
	ENTER;
	
	struct any_form_expression* this = (void*) new_expression(
		ek_any_form,
		&any_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	EXIT;
	return (void*) this;
}

