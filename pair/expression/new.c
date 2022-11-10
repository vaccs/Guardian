
#include <debug.h>

#include <memory/smalloc.h>

#include <expression/inc.h>

#include "struct.h"
#include "new.h"

struct expression_pair* new_expression_pair(
	struct expression* first,
	struct expression* second)
{
	ENTER;
	
	struct expression_pair* this = smalloc(sizeof(*this));
	
	this->first = inc_expression(first);
	this->second = inc_expression(second);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

