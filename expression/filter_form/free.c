
#include <assert.h>

#include <debug.h>

/*#include <list/expression/free.h>*/

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_filter_form_expression(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct filter_form_expression* this = (void*) super;
	
	free_expression(this->lambda);
	
	free_expression_list(this->arguments);
	#endif
	
	EXIT;
}

