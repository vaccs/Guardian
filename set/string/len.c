
#include <debug.h>

#include "struct.h"
#include "len.h"

unsigned stringset_len(
	const struct stringset* this)
{
	return this->n;
}

