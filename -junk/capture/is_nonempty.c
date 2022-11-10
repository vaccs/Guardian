
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool capture_list_is_nonempty(
	struct capture_list* this)
{
	return !!this->n;
}

