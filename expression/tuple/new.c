
#include <debug.h>

/*#include <list/parameter/inc.h>*/

/*#include <list/capture/inc.h>*/

#include <list/expression/inc.h>

#include "../new.h"
#include "../inc.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_tuple_expression(
	struct type* type,
	struct expression_list* subexpressions)
{
	ENTER;
	
	struct tuple_expression* this = (void*) new_expression(
		ek_tuple,
		&tuple_expression_inheritance,
		type,
		sizeof(*this));
	
	this->subexpressions = inc_expression_list(subexpressions);
	
	EXIT;
	return (void*) this;
}

