
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool named_expression_list_is_nonempty(
	const struct named_expression_list* this)
{
	return !!this->n;
}

