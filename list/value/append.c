
#include <debug.h>

#include <value/inc.h>

#include "struct.h"
#include "append.h"

void value_list_append(
	struct value_list* this,
	struct value* element)
{
	ENTER;
	
	if (this->n == this->cap)
	{
		this->cap = this->cap << 1 ?: 1;
		
		dpv(this->cap);
		
		this->data = srealloc(this->data, sizeof(*this->data) * this->cap);
	}
	
	this->data[this->n++] = inc_value(element);
	
	EXIT;
}

