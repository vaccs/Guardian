
#include <debug.h>

#include <expression/inc.h>

#include <type_cache/get_type/float.h>

/*#include <type/free.h>*/

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct expression* new_float_expression(
	struct type_cache* tcache,
	struct expression* subexpression)
{
	ENTER;
	
	struct float_expression* this = (void*) new_expression(
		ek_float,
		&float_expression_inheritance,
		type_cache_get_float_type(tcache),
		sizeof(*this));
	
	this->subexpression = inc_expression(subexpression);
	
	EXIT;
	return (void*) this;
}

