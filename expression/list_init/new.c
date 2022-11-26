
#include <debug.h>

#include <list/expression/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_list_init_expression(
	struct type* type,
	struct expression_list* elements)
{
	ENTER;
	
	struct list_init_expression* this = (void*) new_expression(
		ek_list_init,
		&list_init_expression_inheritance,
		type,
		sizeof(*this));
	
	this->elements = inc_expression_list(elements);
	
	EXIT;
	return (void*) this;
}

