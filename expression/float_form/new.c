
#include <debug.h>

#include <expression/inc.h>

/*#include <type_cache/get_type/float.h>*/

/*#include <type/free.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_float_form_expression(
	struct type* type,
	struct expression* object)
{
	ENTER;
	
	struct float_form_expression* this = (void*) new_expression(
		ek_float_form,
		&float_form_expression_inheritance,
		type,
		sizeof(*this));
	
	this->object = inc_expression(object);
	
	EXIT;
	return (void*) this;
}

