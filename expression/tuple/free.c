
#include <debug.h>

/*#include <list/parameter/free.h>*/

/*#include <list/capture/free.h>*/

#include <list/expression/free.h>

/*#include "../free.h"*/

#include "struct.h"
#include "free.h"

void free_tuple_expression(
	struct expression* super)
{
	ENTER;
	
	struct tuple_expression* this = (void*) super;
	
	free_expression_list(this->subexpressions);
	
	EXIT;
}

