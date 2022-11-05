
#include <debug.h>

#include "struct.h"
#include "append.h"

void string_list_append(
	struct string_list* this,
	struct string* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_string(element);
	
	EXIT;
}

