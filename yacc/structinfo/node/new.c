
#include <debug.h>

#include "struct.h"
#include "new.h"

struct structinfo_node* new_structinfo_node(
	enum structinfo_node_type type,
	struct string* name,
	struct string* grammar,
	char conversion_char)
{
	ENTER;
	
	struct structinfo_node* this = smalloc(sizeof(*this));
	
	this->type = type;
	
	this->name = inc_string(name);
	
	this->grammar = inc_string(grammar);
	
	this->conversion_char = conversion_char;
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

