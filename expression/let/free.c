
#include <assert.h>

#include <debug.h>

#include <list/named_expression/free.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_let_expression(
	struct expression* super)
{
	ENTER;
	
	struct let_expression* this = (void*) super;
	
	free_named_expression_list(this->parameters);
	
	free_expression(this->body);
	
	EXIT;
}

