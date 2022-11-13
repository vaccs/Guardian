
#include <debug.h>

#include <expression/inc.h>

#include <string/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_has_expression(
	struct type* type,
	struct expression* object,
	struct string* fieldname)
{
	ENTER;
	
	struct has_expression* this = (void*) new_expression(
		ek_has,
		&has_expression_inheritance,
		type,
		sizeof(*this));
	
	this->object = inc_expression(object);
	
	this->fieldname = inc_string(fieldname);
	
	EXIT;
	return (void*) this;
}

