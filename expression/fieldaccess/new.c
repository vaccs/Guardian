
#include <debug.h>

#include <expression/inc.h>

#include <type/free.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_fieldaccess_expression(
	struct type* type,
	struct expression* object,
	struct string* fieldname)
{
	ENTER;
	
	struct fieldaccess_expression* this = (void*) new_expression(
		ek_fieldaccess,
		&fieldaccess_expression_inheritance,
		type,
		sizeof(*this));
	
	this->object = inc_expression(object);
	
	this->fieldname = inc_string(fieldname);
	
	EXIT;
	return (void*) this;
}

