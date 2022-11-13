
#include <debug.h>

#include <memory/smalloc.h>

#include <expression/inc.h>

#include "struct.h"
#include "new.h"

struct expression_pair* new_expression_pair(
	struct expression* key,
	struct expression* value)
{
	ENTER;
	
	struct expression_pair* this = smalloc(sizeof(*this));
	
	this->key = inc_expression(key);
	
	this->value = inc_expression(value);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

