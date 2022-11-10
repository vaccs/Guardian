
#include <debug.h>

#include <expression/inc.h>

#include <type_cache/get_type/int.h>

#include <type/free.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_product_expression(
	struct type* type,
	struct expression* list)
{
	ENTER;
	
	struct product_expression* this = (void*) new_expression(
		ek_product,
		&product_expression_inheritance,
		type,
		sizeof(*this));
	
	this->list = inc_expression(list);
	
	EXIT;
	return (void*) this;
}

