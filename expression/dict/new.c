
#include <debug.h>

#include <list/expression_pair/inc.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_dict_expression(
	struct type* type,
	struct expression_pair_list* elements)
{
	ENTER;
	
	struct dict_expression* this = (void*) new_expression(
		ek_dict,
		&dict_expression_inheritance,
		type,
		sizeof(*this));
	
	this->elements = inc_expression_pair_list(elements);
	
	EXIT;
	return (void*) this;
}

