
#include <assert.h>

#include <debug.h>

#include "layer.h"
#include "struct.h"
#include "is_head_pure.h"

bool type_check_scope_is_head_pure(
	struct type_check_scope* this)
{
	ENTER;
	
	assert(this->head);
	
	bool retval = this->head->is_pure;
	
	dpvb(retval);
	
	EXIT;
	return retval;
}

