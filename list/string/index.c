
#include <debug.h>

#include <string/are_equal.h>

#include "struct.h"
#include "index.h"

bool string_list_index(
	const struct string_list* this,
	unsigned *out_index,
	struct string* element)
{
	for (unsigned i = 0, n = this->n; i < n; i++)
		if (strings_are_equal(this->data[i], element))
			return *out_index = i, true;
	
	return false;
}

