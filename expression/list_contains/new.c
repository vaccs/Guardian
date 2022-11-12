
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_list_contains_expression(
	struct type* type,
	struct expression* element,
	struct expression* list)
{
	ENTER;
	
	struct list_contains_expression* this = (void*) new_expression(
		ek_list_contains,
		&list_contains_expression_inheritance,
		type,
		sizeof(*this));
	
	this->element = inc_expression(element);
	
	this->list = inc_expression(list);
	
	EXIT;
	return (void*) this;
}

