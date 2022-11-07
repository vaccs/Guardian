
#include <debug.h>

/*#include <expression/inc.h>*/

/*#include <list/parameter/inc.h>*/

#include <list/value/inc.h>

/*#include <scope/inc.h>*/

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_tuple_value(
	struct type* type,
	struct value_list* subvalues)
{
	ENTER;
	
	struct tuple_value* this = (void*) new_value(
		type,
		vk_tuple,
		&tuple_value_inheritance,
		sizeof(*this));
	
	this->subvalues = inc_value_list(subvalues);
	
	EXIT;
	return (void*) this;
}

