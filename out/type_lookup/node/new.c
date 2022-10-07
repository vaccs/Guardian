
#include <debug.h>

#include "struct.h"
#include "new.h"

struct type_lookup_node* new_type_lookup_node(
	struct type* type,
	struct out_type* otype)
{
	ENTER;
	
	struct type_lookup_node* this = smalloc(sizeof(*this));
	
	this->type = type;
	this->otype = otype;
	
	EXIT;
	return this;
}
