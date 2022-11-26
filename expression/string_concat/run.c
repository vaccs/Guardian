

#include <string.h>
#include <stdlib.h>

#include <debug.h>

/*#include <list/value/new.h>*/
/*#include <list/value/extend.h>*/
/*#include <list/value/free.h>*/

#include <value/string/struct.h>
#include <value/string/new.h>

#include "run.h"

struct value* string_concat_run(
	struct type* type,
	struct string_value* left,
	struct string_value* right)
{
	ENTER;
	
	unsigned len = left->len + right->len;
	
	unsigned char* buffer = malloc(len);
	
	memcpy(mempcpy(buffer, left->chars, left->len), right->chars, right->len);
	
	struct value* value = new_string_value(type, buffer, len);
	
	EXIT;
	return value;
}

