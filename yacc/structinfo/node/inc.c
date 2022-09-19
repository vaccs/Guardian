
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct structinfo_node* inc_structinfo_node(struct structinfo_node* this)
{
	if (this) this->refcount++;
	return this;
}

