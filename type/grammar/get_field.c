
#include <stddef.h>

#include <debug.h>

#include <string/are_equal.h>

#include <named/type/struct.h>

#include <list/named_type/struct.h>

#include "struct.h"
#include "get_field.h"

struct type* grammar_type_get_field(
	struct grammar_type* this,
	struct string* fieldname)
{
	struct type* retval = NULL;
	ENTER;
	
	for (unsigned i = 0, n = this->fields->n; !retval && i < n; i++)
		if (strings_are_equal(fieldname, this->fields->data[i]->name))
			retval = this->fields->data[i]->type;
	
	EXIT;
	return retval;
}
