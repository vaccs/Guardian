
#include <debug.h>

#include <memory/smalloc.h>

#include <string/inc.h>

#include "struct.h"
#include "new.h"

struct type_check_scope_node* new_type_check_scope_node(
	struct string* name,
	struct type* type)
{
	ENTER;
	
	struct type_check_scope_node* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->type = type;
	
	this->value = NULL;
	
	EXIT;
	return this;
}

