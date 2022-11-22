
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_isexecutableby_form_expression(
	struct type* type,
	struct expression* path,
	struct expression* user)
{
	ENTER;
	
	struct isexecutableby_form_expression* this = (void*) new_expression(
		ek_isexecutableby_form,
		&isexecutableby_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->path = inc_expression(path);
	
	this->user = inc_expression(user);
	
	EXIT;
	return (void*) this;
}

