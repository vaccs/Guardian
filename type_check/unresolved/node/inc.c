
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct unresolved_node* inc_unresolved_node(
	struct unresolved_node* this)
{
	if (this) this->refcount++;
	return this;
}

