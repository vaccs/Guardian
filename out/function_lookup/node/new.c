
#include <debug.h>

#include "struct.h"
#include "kind.h"
#include "new.h"

struct function_lookup_node* new_function_lookup_node(
	enum function_lookup_node_kind kind,
	struct type* type,
	unsigned id,
	struct out_function* function)
{
	ENTER;
	
	struct function_lookup_node* this = malloc(sizeof(*this));
	
	this->kind = kind;
	this->type = type;
	this->id = id;
	this->function = function;
	
	EXIT;
	return this;
}


