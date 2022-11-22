
#include <debug.h>

#include <expression/struct.h>
#include <expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_isdir_form_expression(
	struct type* type,
	struct expression* path)
{
	ENTER;
	
	struct isdir_form_expression* this = (void*) new_expression(
		ek_isdir_form,
		&isdir_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->path = inc_expression(path);
	
	EXIT;
	return (void*) this;
}

