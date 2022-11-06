
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct capture* new_capture(
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type)
{
	ENTER;
	
	struct capture* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->kind = kind;
	
	this->type = type;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}


