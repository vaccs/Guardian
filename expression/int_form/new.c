
#include <debug.h>

#include <expression/inc.h>

/*#include <type_cache/get_type/float.h>*/

/*#include <type/free.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_int_form_expression(
	struct type* type,
	struct expression* object)
{
	ENTER;
	
	struct int_form_expression* this = (void*) new_expression(
		ek_int_form,
		&int_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->object = inc_expression(object);
	
	EXIT;
	return (void*) this;
}

