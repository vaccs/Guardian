
#include <debug.h>

#include "struct.h"
#include "new.h"

struct structinfo_node* new_structinfo_node(
	struct string* name,
	enum structinfo_node_type type)
{
	ENTER;
	
	struct structinfo_node* this = smalloc(sizeof(*this));
	
	this->name = inc_string(name);
	
	this->type = type;
	
	EXIT;
	return this;
}

