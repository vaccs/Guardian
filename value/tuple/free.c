
#include <debug.h>

/*#include <list/parameter/free.h>*/

/*#include <expression/free.h>*/

/*#include <scope/free.h>*/

#include <list/value/free.h>

#include "struct.h"
#include "free.h"

void free_tuple_value(
	struct value* super)
{
	ENTER;
	
	struct tuple_value* this = (void*) super;
	
	free_value_list(this->subvalues);
	
	EXIT;
}

