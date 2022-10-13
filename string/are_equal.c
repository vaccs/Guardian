
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "are_equal.h"

bool strings_are_equal(
	const struct string* a,
	const struct string* b)
{
	return a->len == b->len && !strncmp(a->chars, b->chars, a->len);
}

