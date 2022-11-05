
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct zebu_expression_list* inc_zebu_expression_list(
	struct zebu_expression_list* this)
{
	if (this) this->refcount++;
	return this;
}

