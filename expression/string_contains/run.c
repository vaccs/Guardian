
#include <string.h>
#include <stdbool.h>

#include <debug.h>

#include <value/string/struct.h>

#include <value/bool/new.h>

#include "run.h"

struct value* string_contains_run(
	struct type* type,
	struct string_value* substring,
	struct string_value* string)
{
	ENTER;
	
	struct value* value = new_bool_value(type, !!memmem(
		string->chars, string->len,
		substring->chars, substring->len));
	
	EXIT;
	return value;
}

